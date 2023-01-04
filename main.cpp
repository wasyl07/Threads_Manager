#include <iostream>
#include <cstdlib>
#include "include/Tasking.h"
#include <thread>
#include <mutex>
#include <chrono>
#include <fstream>
#include <random>

#include <boost/crc.hpp>

using namespace std;

Tasking::Task_Handler Handler1;
arguments args;

semafora sem;

std::mutex mutex_lock;

double l1 = 0;
double l2 = 100;

std::uniform_real_distribution<double> unif(l1, l2);
std::default_random_engine re;

Tasking::Task::Task_State Generate_Data()
{
    std::vector<double> tmp;
    std::lock_guard<std::mutex> guard(mutex_lock);
    //args.inputs.clear();
    for(int i = 0; i<100; i++)
    {
        double val1 = unif(re);
        tmp.push_back(val1);
    }
    sem.compute = true;
    args.inputs.push_back(tmp);
    cout << "Block created, size: "<< tmp.size() << endl;
    cout << "Blocks number: " << args.inputs.size() << endl;
    return Tasking::Task::Task_State::COMPLETED;
}

Tasking::Task::Task_State Calculate()
{
    cout << "computing input number: " << args.inputs.size() << endl;
    std::lock_guard<std::mutex> guard(mutex_lock);
    if(args.inputs.size() !=0)
    {
        vector<double> tmp = args.inputs.back();
        args.inputs.pop_back();
        double sum = 0;
        for(int i = 0; i<tmp.size(); i++)
        {
            sum += tmp[i];
            cout << tmp[i] <<endl;
        }
        double mean_value = sum/tmp.size();
        cout << "sum: "<< sum << " i: " << tmp.size() << " mean value: " << mean_value << endl;
        args.output.push_back(mean_value);
    }
    return Tasking::Task::Task_State::COMPLETED;
}
int main(int, char **)
{  
    int blocks = 0;

    while(args.output.size() != 10)
    {
        if(blocks < 10)
        {
            Tasking::Task *Generate = new Tasking::Task(&Generate_Data ,true);
            blocks++;
        }
        if(args.inputs.size() > 0)
        {
            Tasking::Task *calculate = new Tasking::Task(&Calculate ,true);
        }
    }
    //Handler1.End_Tasks();
    for(int i = 0; i<args.output.size(); i++)
    {
        cout << i <<". mean value = " << args.output[i] << endl;
    }
    cout << Handler1.get_number_of_tasks();
    return 0;
}
