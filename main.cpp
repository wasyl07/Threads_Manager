#include <iostream>
#include <cstdlib>
#include "include/Tasking.h"
#include <thread>
#include <mutex>
#include <chrono>
#include <fstream>
#include <random>

using namespace std;

Tasking::Task_Handler Handler1;
arguments args_global;

Tasking::Task::Task_State Read_Data(arguments args)
{
    cout << "Generate_Data -> " << args.x << endl;
    return Tasking::Task::Task_State::COMPLETED;
}
Tasking::Task::Task_State Modify_Data(arguments args)
{
    args_global.x = 3;
    return Tasking::Task::Task_State::COMPLETED;
}

int main(int, char **)
{  
    args_global.x = 2;
    Tasking::Task ReadTask(&Read_Data, args_global ,true);
    Tasking::Task WriteTask(&Modify_Data, args_global ,true);
    Tasking::Task ReadTask2(&Read_Data, args_global ,true);

    Handler1.Start_all_Tasks();

    Handler1.End_Tasks();

    return 0;
}
