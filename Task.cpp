#include "include/Task_Manager.hpp"

using namespace std;
using namespace Tasking;

extern Task_Handler Handler1;

Tasking::Task::Task(Task_State(*fun_ptr)(arguments), arguments arg, bool go)
{
    ptr_arguments = fun_ptr;
    args = arg;
    //id = Handler1.add_task(this);
    if(go == true)
    {
        this->Execute_Task(fun_ptr, arg);
    }
}
void Tasking::Task::Start_Task()
{
    Execute_Task(ptr_arguments, args);
}

Task::Task_State Task::join()
{
    t->join();
    t = nullptr;
    return Task_State::COMPLETED;
}

void Tasking::Task::Show_Task_Info()
{
    cout << "Task number: " << id << " State:" 
    << state << " Thread id:" << t->get_id() << " Is task running?: " << Is_Task_Running() << endl;
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

template <typename Function, typename Argument>
void Task::Execute_Task(Function func, Argument arg)
{
    Handler1.Lock_Mutex();
    t = new std::thread(func, args);
    state = IN_PROGRESS;
}
