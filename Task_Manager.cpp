#include <iostream>
#include <vector>
#include "include/Task_Manager.hpp"

using namespace Tasking;

Task_Handler Handler1;

Tasking::Task::Task(void(*fun_ptr)(),void* arg)
{
    Handler1.add_task(this);


}