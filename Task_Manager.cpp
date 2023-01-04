#include <iostream>
#include <vector>
#include "include/Task_Manager.hpp"

using namespace Tasking;
using namespace std;

extern Task_Handler Handler1;

int Tasking::Task_Handler::add_task(Task *newtask)
{
    Handler1.active_tasks.push_back(newtask);
    cout << "Task: " << active_tasks.size() << " added" << endl;
    return active_tasks.size();
}
Task_Handler::Operation_State Task_Handler::Start_all_Tasks()
{
    for(Task *t : Handler1.active_tasks)
    {
        t->Start_Task();
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
    return Task_Handler::Operation_State::OK;
}
Task_Handler::Operation_State Task_Handler::Purge()
{
    active_tasks.clear();
    return Task_Handler::Operation_State::OK;
}
Task_Handler::Operation_State Task_Handler::Print_Threads_ID()
{
    for(Task *task : Handler1.active_tasks)
    {
        cout << "Task thread id: " << task->return_thread_id() << endl;
    }   
    return Task_Handler::Operation_State::OK;
}

int Task_Handler::get_number_of_tasks()
{
    return active_tasks.size();
}

void Task_Handler::FIFO_Algorithm()
{
    if(active_tasks.size() != 0)
    {
        cout << "Number of active tasks: " << active_tasks.size() << endl;
        //active_tasks.back()->t->detach();
        //active_tasks.pop_back();
    }
}