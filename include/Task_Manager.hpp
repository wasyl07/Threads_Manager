#pragma once
#include <vector>
#include <thread>
#include <iostream>
namespace Tasking
{
    //forward declaration.
    class Task;

    class Task_Handler {
        private:
            enum class Operation_State{
                OK,
                FAIL,
                DEFAULT
            };

            std::vector<Task> active_tasks;


        public:
        Task_Handler()
        {
            std::cout<< "Task handler online!"<<std::endl;
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

    class Task{
        private:

            int id;
            void* pointer_to_arguments;
            int position_in_vector;
            void(*ptr)();

        public:

            
            Task(void(*fun_ptr)(), void* arg);  

            enum Task_State{
                OK,
                FAIL,
                IN_PROGRESS,
                PAUSED,
                COMPLETED,
                DEFAULT
            };

            Task_State state = Task_State::DEFAULT;

            Task_State start()
            {
                std::thread th(ptr);
                return Task_State::IN_PROGRESS;
            }
            Task_State join()
            {
                std::cout << "Task completed" << std::endl;
                return Task_State::COMPLETED;
            }

            Task_State return_state()
            {
                return state;
            }
    }; 
}
