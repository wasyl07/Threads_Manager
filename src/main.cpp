#include <iostream>
#include <cstdlib>
#include "../include/Tasking.h"
#include <thread>
#include <mutex>
#include <chrono>
#include <fstream>
#include <random>

//Dodać kolejkę tasków do wykonania, i możliwość ograniczenia wykonywanych tasków naraz. DONE
//Dodać sygnalizację zakończenia pracy. DONE 

using namespace std;

Tasking::Task_Handler Handler1;
arguments args_global;

Tasking::Task::Task_State Read_Data(arguments args)
{
    cout << "Generate_Data -> " << args_global.x << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));


    Handler1.Resolve_thread_anonymity(std::this_thread::get_id());
    return Tasking::Task::Task_State::COMPLETED;
}

Tasking::Task::Task_State Modify_Data(arguments args)
{
    args_global.x = rand()%99 + 1;
    cout << "Modify_Data ->" << args_global.x << endl;

    return Tasking::Task::Task_State::COMPLETED;
}

int main(int, char **)
{  
    for(int i=0;i<8;i++)
    {
          Tasking::Task *ReadTask = new Tasking::Task(&Read_Data, args_global ,false);
    }
    //Tasking::Task WriteTask(&Modify_Data, args_global ,false);

    //ReadTask.Set_Task_As_Cyclic(1000);
    //WriteTask.Set_Task_As_Cyclic(1000);

    Handler1.Select_FIFO(4);

    //Handler1.Cycle_Tasks();
    while(true){}

    return 0;
}
