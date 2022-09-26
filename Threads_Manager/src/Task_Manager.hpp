#pragma once
#include "Console.hpp"
#include <vector>


namespace Tasking
{
    //Thread forward declaration.
    class Task;

    class Task_Handler {
        private:
            enum class Operation_State{
                OK,
                FAIL,
                DEFAULT
            };

            Console_Handler console;

            std::vector<Task> active_tasks;
            std::vector<Task> Paused_tasks;

        public:
        Task_Handler()
        {
            console.Display("task handler online!");
        }
        int add_task(Task *newtask)
        {
            return 0;
        }
        Operation_State pause_task(Task);
        Operation_State resume_task(Task);
        Operation_State delete_task(Task);
        Operation_State get_task_state(Task);
        Operation_State get_task_progress(Task);
    };

Task_Handler handler;

    class Task{
        private:
            pthread_t thread;
            void* (*pointer_to_task)(void*);
            int id;
            void* pointer_to_arguments;
            int position_in_vector;
        public:
            Task() = default;
            Task(void* (fun_ptr)(void*), void* arg)
            {
                pointer_to_task = fun_ptr;
                pointer_to_arguments = arg;
                handler.add_task(this);
                state = static_cast<Task_State>(pthread_create(&thread, nullptr, fun_ptr, arg));
            }
            enum class Task_State{
                OK,
                FAIL,
                IN_PROGRESS,
                PAUSED,
                COMPLETED,
                DEFAULT
            };

            Task_State state = Task_State::DEFAULT;

            Task_State return_state()
            {
                return state;
            }
    };
}
