#pragma once

#include <vector>
#include <thread>
#include <iostream>
#include <future>
#include "arguments.hpp"
#include <ctime>

typedef std::chrono::time_point<std::chrono::steady_clock> period_time;

namespace Tasking
{
    struct timer{
        int milis;
        bool waiting;
        std::chrono::time_point<std::chrono::steady_clock> ref;
    };

    class Task;
    class Task_Handler {
        private:
            std::mutex Handler_mutex;
            std::thread *manage_cyclic_tasks;
            std::thread *manage_FIFO_queue;
            int max_number_of_threads;
            bool FIFO_Mode = false;
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
        struct signals{
            int  thread_id;
            bool thread_ended;
        };
        std::vector<Task*> active_tasks;
        std::vector<Task*> queue;

        int add_task(Task *newtask);
        Operation_State Resolve_thread_anonymity(std::thread::id _id);

        Operation_State pause_task(Task);
        Operation_State resume_task(Task);
        Operation_State delete_task(Task);
        Operation_State get_task_state(Task);

        int get_number_of_tasks();

        Operation_State End_Tasks();
        Operation_State Spin_Tasks();
        Operation_State Start_all_Tasks();
        Operation_State Show_active_tasks();
        Operation_State Print_Threads_ID();
        Operation_State Purge();
        Operation_State Select_FIFO(int num_of_threads);

        void Cycle_Tasks();
        void FIFO_Algorithm();
        void Spin();

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
            struct timer{
                std::chrono::milliseconds milis;
                period_time ref;
                bool waiting = false;
            }time;
        private:
            int id;
            bool run;
            //Zmienna cyclic przyjmuje domyślnie wartość false;
            bool cyclic = false;
            bool is_task_running = false;
            std::thread *t = nullptr;
            arguments args;
            Task_State(*ptr_arguments)(arguments);
        public:
            //Konstruktor
            Task(Task_State(*fun_ptr)(arguments), arguments arg, bool go);  
            //Metody do rozpoczynania i kończenia pracy wątków.
            void Start_Task();
            Task_State join();
            void Set_Task_As_Cyclic(int _milis);
            //Metody pokazujące dane i stan obiektów task.
            void Show_Task_Info();
            bool Is_Task_Running();
            //Metody zwracające dane na temat obiektu Task.
            Task_State return_state() {return state;}
            int return_id() {return id;}
            std::thread::id return_thread_id() {return t->get_id();}
            bool return_cyclic() {return cyclic;}
            void Try_Start();
        private:
            //Metoda tworząca obiekt std::thread.
            template <typename Function, typename Argument>
            void Execute_Task(Function func, Argument arg);
            //Metoda zwracająca wskaźnik do obiektu std::thread.
            std::thread* Return_thread() {return t;}
            bool Period();
    };
}
