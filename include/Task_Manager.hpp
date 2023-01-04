#pragma once
#include <vector>
#include <thread>
#include <iostream>
#include <future>
#include "arguments.hpp"

namespace Tasking
{
    class Task;
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
        std::vector<Task*> active_tasks;

        int add_task(Task *newtask);
        Operation_State pause_task(Task);
        Operation_State resume_task(Task);
        Operation_State delete_task(Task);
        Operation_State get_task_state(Task);
        Operation_State get_task_progress(Task);

        int get_number_of_tasks();

        Operation_State End_Tasks();
        Operation_State Start_all_Tasks();
        Operation_State Show_active_tasks();
        Operation_State Purge();

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
            }state;
            std::thread *t;
        private:

            int id;
            input_images input;
            arguments args;
            bool run;
            Task_State(*ptr)(input_images);
            Task_State(*ptr_arguments)(arguments);
            Task_State(*ptr_bool)();
            Task_State(*ptr_void)();
            bool is_task_running;

        public:
            std::thread* Return_thread() {return t;}
            //Constructors
            Task(Task_State(*fun_ptr)(input_images), input_images arg);  
            Task(Task_State(*fun_ptr)(arguments), arguments arg, bool go);  
            Task(Task_State(*fun_ptr)());  
            Task(Task_State(*fun_ptr)()        ,bool go);  
            Task_Handler::Operation_State start();
            Task_State join();
            Task_State return_state() {return state;}
            int return_id() {return id;}
            void Show_Task_Info();
            bool Is_Task_Running() ;
    }; 
}
