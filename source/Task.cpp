#include "Task_Manager.hpp"

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
    state = CREATED;
    if(go == true)
    {
        this->Execute_Task(ptr_arguments, args);
    }
}
/**
 * Rozpocznij pracę
 *
 * Metoda ta rozpoczyna prace wątku.
 *
 * @param none
 * @return none
 */
void Tasking::Task::Start_Task()
{
    is_task_running = true;
    Execute_Task(ptr_arguments, args);
}
/**
 * Zakończ wątek.
 *
 * Metoda ta kończy pracę wątku.
 *
 * @param  none
 * @return Stan obiektu Task.
 */
Task::Task_State Task::join()
{
    if(t != nullptr && (*t).joinable())
    {
        t->join();
        delete t;
        //t = nullptr;
        state = COMPLETED;
        time.waiting = false;
        is_task_running = false;
        time.ref = std::chrono::steady_clock::now();
    }
    else{
        cout << "Task was not started. Dont try to join it!" << endl;
    }
    return state;
}
/**
 * Ustaw okresowość
 *
 * Metoda umożliwia okresowe wykonywanie się zadania
 *
 * @param milis Określa okres zadania w milisekundach
 * @return none
 */
void Task::Set_Task_As_Cyclic(int _milis)
{
    cyclic = true; 
    time.milis = std::chrono::milliseconds(_milis);
}
/**
 * Pokaż informacje o wątku
 *
 * Metoda wypisuje atrybuty wątku takie jak: Numer, stan, identyfikator wątku oraz czy wątek pracuje.
 *
 * @param none
 * @return none
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
 * Metoda informuje o tym czy wątek pracuje.
 *
 * @param  none
 * @return true jeśli pracuje, false jeśli nie.
 */
bool Task::Is_Task_Running() 
{
    try{
        if(t != nullptr)
        {
            return true;
        }
        else
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
 * Wykonaj zadanie.
 *
 * Metoda ta powołuje do życia wątek std::thread, co rozpoczyna jego pracę oraz blokuje mutex.
 *
 * @param  func Wskaźnik do funkcji która będzie wykonywana przez wątek.
 * @param  arg Argumenty przekazywane do wątku.
 * @return none
 */
void Task::Try_Start()
{
    if((time.waiting == false) && (is_task_running == false))
    {
        time.waiting = Period();
    }
    else
    {
        Start_Task();
    }
}
/**
 * Wykonaj zadanie.
 *
 * Metoda ta powołuje do życia wątek std::thread, co rozpoczyna jego pracę oraz blokuje mutex.
 *
 * @param  func Wskaźnik do funkcji która będzie wykonywana przez wątek.
 * @param  arg Argumenty przekazywane do wątku.
 * @return none
 */
template <typename Function, typename Argument>
void Task::Execute_Task(Function func, Argument arg)
{
    state = Task::IN_PROGRESS;
    Handler1.Lock_Mutex();
    t = new std::thread(func, args);
}
/**
 * Sprawdź okres.
 *
 * Metoda ta sprawdza czy minął okres po którym zadanie musi zostać uruchomione ponownie
 *
 * @param  none 
 * @return none
 */
bool Task::Period()
{
    if((std::chrono::steady_clock::now() - time.ref  > time.milis))
    {
        return true;
    }
    return false;
}
