#pragma once
#include "Console.hpp"
#include "Thread.hpp"
#include <vector>

namespace Threading
{
    class Thread_Handler{
        private:
            enum class Operation_State{
                OK,
                FAIL,
                DEFAULT
            };

            Console_Handler console;

            std::vector<Thread> Active_Threads;
            std::vector<Thread> Paused_Threads;

        public:
        Thread_Handler()
        {
            console.Display("Thread handler online!");
        }
        Operation_State create_thread(Thread);
        Operation_State add_thread(Thread);
        Operation_State pause_thread(Thread);
        Operation_State resume_state(Thread);
        Operation_State delete_thread(Thread);
        Operation_State get_thread_state(Thread);
        Operation_State get_thread_progress(Thread);
    };
}