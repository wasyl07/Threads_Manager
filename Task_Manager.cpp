#include <iostream>
#include <vector>
#include "include/Task_Manager.hpp"

using namespace Tasking;
using namespace std;

extern Task_Handler Handler1;

Tasking::Task::Task(Task_State(*fun_ptr)(input_images), input_images arg)
{
    ptr = fun_ptr;
    input = arg;
    id = Handler1.add_task(this);
    Task::state = CREATED;

    Show_Task_Info();
}
Tasking::Task::Task(Task_State(*fun_ptr)(arguments), arguments arg, bool go)
{
    ptr_arguments = fun_ptr;
    args = arg;
    id = Handler1.add_task(this);
    if(go == true)
    {
        this->start();
    }
}
Tasking::Task::Task(Task_State(*fun_ptr)(), bool go)
{
    ptr_bool = fun_ptr;
    run = go;
    id = Handler1.add_task(this);
    if(go == true)
    {
        this->start();
    }
}

Tasking::Task::Task(Task_State(*fun_ptr)())
{


}

int Tasking::Task_Handler::add_task(Task *newtask)
{
    Handler1.active_tasks.push_back(newtask);
    cout << "Task: " << active_tasks.size() << " added" << endl;
    return active_tasks.size();
}
void Tasking::Task::Show_Task_Info()
{
    cout << "Task number: " << id << " State:" 
    << state << " this:" << this << " Is task running?: " << Is_Task_Running() << endl;
}
Task_Handler::Operation_State Task_Handler::Start_all_Tasks()
{
    for(Task *t : Handler1.active_tasks)
    {
        t->start();
    }

    return Task_Handler::Operation_State::OK;
}
Task_Handler::Operation_State Task_Handler::Show_active_tasks()
{
    for(Task *t : Handler1.active_tasks)
    {
        t->Show_Task_Info();
    }
    return Task_Handler::Operation_State::OK;
}

Task_Handler::Operation_State Task_Handler::End_Tasks()
{
    for (std::vector<Task*>::iterator it = active_tasks.begin(); it != active_tasks.end();)
    {
        if((*it)->Is_Task_Running() == true)
        {
            (*it)->join();
            (*it)->state = Task::Task_State::COMPLETED;  
            active_tasks.erase(it);
        }
    }
    /*
    for(Task *t : Handler1.active_tasks)
    {
        if(t->Is_Task_Running() == true)
        {
            t->join();
            t->state = Task::Task_State::COMPLETED;   
        }
    }
    */
    return Task_Handler::Operation_State::OK;
}
Task_Handler::Operation_State Task_Handler::Purge()
{
    active_tasks.clear();
    return Task_Handler::Operation_State::OK;
}

Task_Handler::Operation_State Task::start()
{
    t = new std::thread(ptr_bool);
    state = IN_PROGRESS;
    std::cout << "Task id:" << id << " State:" << state << std::endl;
    return Task_Handler::Operation_State::OK; 
}
int Task_Handler::get_number_of_tasks()
{
    return active_tasks.size();
}
Task::Task_State Task::join()
{
    t->join();
    t = nullptr;
    return Task_State::COMPLETED;
}
bool Task::Is_Task_Running() 
{
    try{
        if(Return_thread())
        {
            return true;
        }else
        {
            return false;
        }
    }
    catch(std::runtime_error &e)
    {
        return 0;
    }
}
void Task_Handler::FIFO_Algorithm()
{
    if(active_tasks.size() != 0)
    {
        cout << "Number of active tasks: " << active_tasks.size() << endl;
        active_tasks.back()->start();
        //active_tasks.back()->t->detach();
        //active_tasks.pop_back();
    }
}