#include <iostream>
#include <vector>
#include "Task_Manager.hpp"

using namespace Tasking;

//**************Declared by user**********************//

struct arguments{
    int a;
    double b;
};


void* print_message_function( void* ptr );

//****************************************************//
void Setup_Threads()
{
    //******** Done by user *************************//
    arguments args{1,2.0};
    //void *(*fun_ptr)(void*) = print_message_function; obsolete.
    //Create pointer to a void* function.
    auto const fun_ptr2 = print_message_function;
    //Create pointer to arguments struct.
    auto const arg = &args;
    //Create thread.
    Task my_task(fun_ptr2, (void*)(&arg));
}
/*
Thread_Handler::Operation_State Thread_Handler::add_thread(void *(*fun_ptr) (void*), void* arg)
{  
    return Operation_State::OK;

}
*/