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
arguments args;

Tasking::Task::Task_State Generate_Data(arguments args)
{
    cout << "Generate_Data -> " << args.x << endl;
    return Tasking::Task::Task_State::COMPLETED;
}

int main(int, char **)
{  
    args.x = 2;
    Tasking::Task New_Task(&Generate_Data, args ,true);
    New_Task.join();
    return 0;
}
