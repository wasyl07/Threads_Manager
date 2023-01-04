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
            std::mutex Handler_mutex;
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

        int get_number_of_tasks();

        Operation_State End_Tasks();
        Operation_State Start_all_Tasks();
        Operation_State Show_active_tasks();
        Operation_State Print_Threads_ID();
        Operation_State Purge();

        void FIFO_Algorithm();
        void Spin_lock();

        void Lock_Mutex(){std::lock_guard<std::mutex> guard(Handler_mutex);}
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
        private:
            int id;
            bool run;
            bool is_task_running;
            std::thread *t;
            arguments args;
            Task_State(*ptr_arguments)(arguments);
        public:
            //Konstruktor
            Task(Task_State(*fun_ptr)(arguments), arguments arg, bool go);  
            //Metody do rozpoczynania i kończenia pracy wątków.
            void Start_Task();
            Task_State join();
            //Metody pokazujące dane i stan obiektów task.
            void Show_Task_Info();
            bool Is_Task_Running();
            //Metody zwracające dane na temat obiektu Task.
            Task_State return_state() {return state;}
            int return_id() {return id;}
            std::thread::id return_thread_id() {return t->get_id();}
        private:
            //Metoda tworząca obiekt std::thread.
            template <typename Function, typename Argument>
            void Execute_Task(Function func, Argument arg);
            //Metoda zwracająca wskaźnik do obiektu std::thread.
            std::thread* Return_thread() {return t;}
    };

    
}
