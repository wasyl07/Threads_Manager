#include <iostream>
#include <vector>
#include "Threads_Manager.hpp"

std::vector<int> vc1 {0,1,2,3,4};

using namespace Threading;

Thread_Handler handler;
//**************Declared by user**********************//

struct arguments{
    int a;
    double b;
};


void *print_message_function( void* ptr);

//****************************************************//
void Setup_Threads()
{
    //******** Done by user *************************//
    arguments args{1,2.0};
    //void *(*fun_ptr)(void*) = print_message_function; obsolete.
    //Create pointer to a void* function.
    auto *fun_ptr2 = print_message_function;
    //Create pointer to arguments struct.
    auto *arg = &args;
    //Create thread.
    Thread my_thread(fun_ptr2, (void*)(&arg));
}

Thread_Handler::Operation_State Thread_Handler::add_thread(void *(*fun_ptr) (void*), void* arg)
{  
    return Operation_State::OK;

}