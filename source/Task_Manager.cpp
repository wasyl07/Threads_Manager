#include <iostream>
#include <vector>
#include "Task_Manager.hpp"

using namespace Tasking;
using namespace std;


Task_Handler Handler1;

/**
 * Dodaj do vectora.
 *
 * Metoda dodaje nowo utworzony obiekt Task do vectora active_tasks.
 *
 * @param newtask Wskaźnik do obiektu Task.
 * @return Liczbę obiektów w wektorze.
 */
int Tasking::Task_Handler::add_task(Task *newtask)
{
    Handler1.active_tasks.push_back(newtask);
    //cout << "Task: " << active_tasks.size() << " added" << endl;
    return active_tasks.size();
}
/**
 * Dodaj do vectora.
 *
 * Metoda dodaje nowo utworzony obiekt Task do vectora active_tasks.
 *
 * @param newtask Wskaźnik do obiektu Task.
 * @return Liczbę obiektów w wektorze.
 */
Task_Handler::Operation_State Task_Handler::Resolve_thread_anonymity(std::thread::id _id)
{
    for(Task *t : active_tasks)
    {
        if(_id == t->return_thread_id())
        {
            cout << "Its a match! " << _id << " " << t->return_thread_id() << endl;
            t->state = Task::COMPLETED;
        }
    }
    return Task_Handler::Operation_State::OK;
}
/**
 * Rozpocznij pracę.
 *
 * Metoda uruchamia pracę wszystkich wątków w vectorze.
 *
 * @param  none
 * @return Stan operacji. true jeśli się udało, false jeśli nie.
 */
Task_Handler::Operation_State Task_Handler::Start_all_Tasks()
{
    for(Task *t : Handler1.active_tasks)
    {
        t->Start_Task();
    }

    return Task_Handler::Operation_State::OK;
}
/**
 * Pokaż informacje
 *
 * Wypisuje informacje o aktualnie stworzonych obiektach Task.
 *
 * @param  none
 * @return Stan operacji. true jeśli się udało, false jeśli nie.
 */
Task_Handler::Operation_State Task_Handler::Show_active_tasks()
{
    for(Task *t : Handler1.active_tasks)
    {
        t->Show_Task_Info();
    }
    return Task_Handler::Operation_State::OK;
}
/**
 * Zakończ pracę
 *
 * Kończy prace wszystkich wątków w vectorze.
 * 
 * @param  none
 * @return Stan operacji. true jeśli się udało, false jeśli nie.
 */
Task_Handler::Operation_State Task_Handler::End_Tasks()
{
    for (std::vector<Task*>::iterator it = active_tasks.begin(); it != active_tasks.end();)
    {
        if((*it)->Is_Task_Running() == true)
        {
            (*it)->join();
            (*it)->state = Task::Task_State::COMPLETED;  
            active_tasks.erase(it);
        }
    }
    return Task_Handler::Operation_State::OK;
}
/**
 * Zakończ pracę
 *
 * Kończy prace wszystkich wątków w vectorze.
 * 
 * @param  none
 * @return Stan operacji. true jeśli się udało, false jeśli nie.
 */
Task_Handler::Operation_State Task_Handler::Spin_Tasks()
{
    for (std::vector<Task*>::iterator it = active_tasks.begin(); it != active_tasks.end(); it++)
    {
        if((*it)->Is_Task_Running() == true)
        {
            (*it)->join();
            (*it)->state = Task::Task_State::COMPLETED;  
        }
    }
    return Task_Handler::Operation_State::OK;
}
/**
 * Usuń obiekty
 *
 * Usuwa wszystkie obiekty Task z vectora.
 *
 * @param  go Zmienna określający czy wątek ma rozpocząć pracę odrazu po utworzeniu obiektu.
 * @return Stan operacji. true jeśli się udało, false jeśli nie.
 */
Task_Handler::Operation_State Task_Handler::Purge()
{
    active_tasks.clear();
    return Task_Handler::Operation_State::OK;
}
/**
 * Pokaż ID
 *
 * Wypisuje identyfikatory pracujących wątków.
 *
 * @param  none
 * @return Stan operacji. true jeśli się udało, false jeśli nie.
 */
Task_Handler::Operation_State Task_Handler::Select_FIFO(int num_of_threads)
{
    max_number_of_threads = num_of_threads;
    queue = active_tasks;
    Purge();
    manage_FIFO_queue = new std::thread(&Task_Handler::FIFO_Algorithm, this);
    return Operation_State::OK;
}
/**
 * Pokaż ID
 *
 * Wypisuje identyfikatory pracujących wątków.
 *
 * @param  none
 * @return Stan operacji. true jeśli się udało, false jeśli nie.
 */
Task_Handler::Operation_State Task_Handler::Print_Threads_ID()
{
    for(Task *task : Handler1.active_tasks)
    {
        cout << "Task thread id: " << task->return_thread_id() << endl;
    }   
    return Task_Handler::Operation_State::OK;
}
/**
 * Metoda pokazuje liczbę aktualnie utworzonych obiektów Task.
 *
 * @param  none
 * @return Liczba obiektów Task.
 */
int Task_Handler::get_number_of_tasks()
{
    return active_tasks.size();
}
/**
 * Konstruktor obiektu Task.
 *
 * Tworzy nowy obiekt o typie Task.
 *
 * @param  fun_ptr Wskaźnik do funkcji która będzie wykonywana przez wątek.
 * @param  arg Argumenty przekazywane do wątku.
 * @param  go Zmienna określający czy wątek ma rozpocząć pracę odrazu po utworzeniu obiektu.
 * @return Stan obiektu Task.
 */
/**
 * Wykonaj cyklicznie
 *
 * Metoda przegląda zadania w wektorze active_tasks, i wykonuje te które są ozanczone jako okresowe.
 *
 * @param  none 
 * @return none
 */
void Task_Handler::Cycle_Tasks()
{
    manage_cyclic_tasks = new std::thread(&Task_Handler::Spin, this);
}
/**
 * Wykonaj kolejkę FIFO.
 *
 * Metoda przegląda zadania w wektorze active_tasks, i wykonuje te które są ozanczone jako okresowe.
 *
 * @param  none 
 * @return none
 */
void Task_Handler::FIFO_Algorithm()
{
    while(true)
    {
        while(active_tasks.size() < max_number_of_threads)
        {
            active_tasks.push_back(queue.back());
            queue.pop_back();
        }
        Start_all_Tasks();
        Spin_Tasks();
        while(active_tasks.size() != 0)
        {
            queue.push_back(active_tasks.back());
            active_tasks.pop_back();
        }
    }
}
/**
 * Wykonaj cyklicznie
 *
 * Metoda przegląda zadania w wektorze active_tasks, i wykonuje te które są ozanczone jako okresowe.
 *
 * @param  none 
 * @return none
 */
void Task_Handler::Spin()
{
    do{ 
        for(Task* t : active_tasks)
        {
            if(t->return_cyclic())
            {
                t->Try_Start();
            }
        }
        Spin_Tasks();
    }
    while(true);
}