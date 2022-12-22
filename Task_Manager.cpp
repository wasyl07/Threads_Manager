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
    for(Task *t : Handler1.active_tasks)
    {
        t->join();
        t->state = Task::Task_State::COMPLETED;
        //Handler1.active_tasks.erase(active_tasks.begin());
        //delete t;
     
    }
    return Task_Handler::Operation_State::OK;
}