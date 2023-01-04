#include "include/Task_Manager.hpp"

using namespace std;
using namespace Tasking;

extern Task_Handler Handler1;

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
Tasking::Task::Task(Task_State(*fun_ptr)(arguments), arguments arg, bool go)
{
    ptr_arguments = fun_ptr;
    args = arg;
    id = Handler1.add_task(this);
    if(go == true)
    {
        this->Execute_Task(ptr_arguments, args);
    }
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
void Tasking::Task::Start_Task()
{
    Execute_Task(ptr_arguments, args);
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
Task::Task_State Task::join()
{
    t->join();
    t = nullptr;
    return Task_State::COMPLETED;
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
void Tasking::Task::Show_Task_Info()
{
    cout 
    << "Task number: " << id 
    << " State:" << state
    << " Thread id:" << t->get_id() 
    << " Is task running?: " << Is_Task_Running() 
    << endl;
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
bool Task::Is_Task_Running() 
{
    try{
        if(Return_thread()->joinable())
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
template <typename Function, typename Argument>
void Task::Execute_Task(Function func, Argument arg)
{
    Handler1.Lock_Mutex();
    t = new std::thread(func, args);
    state = IN_PROGRESS;
}
