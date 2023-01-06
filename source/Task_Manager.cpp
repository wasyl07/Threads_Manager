#include <iostream>
#include <vector>
#include "Task_Manager.hpp"

using namespace Tasking;
using namespace std;

extern Task_Handler Handler1;

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
void Task_Handler::FIFO_Algorithm()
{
    if(active_tasks.size() != 0)
    {
        cout << "Number of active tasks: " << active_tasks.size() << endl;
    }
}