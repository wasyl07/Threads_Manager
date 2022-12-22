#pragma once
#include <vector>
#include <thread>
#include <iostream>
#include <future>

#include "arguments.hpp"

namespace Tasking
{
    //forward declaration.
    class Task;
    //Class to store and handle tasks created by user.
    class Task_Handler {
        private:

        public:
        Task_Handler()
        {
            std::cout<< "Task handler online!"<<std::endl;
        }

        enum class Operation_State{
                OK,
                FAIL,
                DEFAULT
            };

        int add_task(Task *newtask);

        std::vector<Task*> active_tasks;

        Operation_State pause_task(Task);
        Operation_State resume_task(Task);
        Operation_State delete_task(Task);
        Operation_State get_task_state(Task);
        Operation_State get_task_progress(Task);

        Operation_State End_Tasks();
        Operation_State Start_all_Tasks();
        Operation_State Show_active_tasks();

        void FIFO_Algorithm();
        void Spin_lock();
    };

    class Task{
        public:
              enum Task_State{
                CREATED,
                FAIL,
                IN_PROGRESS,
                PAUSED,
                COMPLETED,
                DEFAULT
            };

        private:
            int id;
            input_images input;
            Task_State(*ptr)(input_images);
            std::thread *t;
            bool is_task_running;

        public:

            Task(Task_State(*fun_ptr)(input_images), input_images arg);  

            Task_State state = Task_State::DEFAULT;

            Task_Handler::Operation_State start()
            {
                t = new std::thread(ptr, input);
                state = IN_PROGRESS;
                std::cout << "Task id:" << id << " State:" << state << std::endl;
                return Task_Handler::Operation_State::OK; 
            }
            Task_State join()
            {
                t->join();
                t = nullptr;
                return Task_State::COMPLETED;
            }

            Task_State return_state() {return state;}
            int return_id() {return id;}
            void Show_Task_Info();
            bool Is_Task_Running() 
            {
                try{
                    if(t)
                    {
                        return true;
                    }else
                    {
                        return false;
                    }
                }
                catch(std::runtime_error &e)
                {
                    return 0;
                }
            }
    }; 
}
