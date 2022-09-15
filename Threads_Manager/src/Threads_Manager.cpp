#include <iostream>
#include <vector>
#include "Threads_Manager.hpp"

std::vector<int> vc1 {0,1,2,3,4};

using namespace Threading;

Thread_Handler hanlder;
Thread calculate_something;
Thread calculate_something_else;

void say_hello(){
    std::cout << "Hello, from Threads_Manager!\n";
}

Thread_Handler::Operation_State Thread_Handler::create_thread(Thread th1)
{

    return Operation_State::OK;
}