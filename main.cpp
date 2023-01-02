#include <iostream>
#include <cstdlib>
#include "include/Tasking.h"
#include <thread>
#include <mutex>
#include <chrono>
#include <fstream>

using namespace std;

Tasking::Task_Handler Handler1;

std::mutex output_mutex;

Tasking::Task::Task_State Assigment()
{
    return Tasking::Task::Task_State::COMPLETED;
}

int main(int, char **)
{  
    //Tasking::Task *new_task = new Tasking::Task(&Assigment, Image[i][j]);
    return 0;
}
 