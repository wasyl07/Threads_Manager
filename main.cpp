#include <iostream>
#include <cstdlib>
#include "include/Tasking.h"
#include <functional>

using namespace std;

struct arguments{
    int a;
    int b;
}args; 

void task1()
{
    cout<< "Task in progress" << endl;
}

int main(int, char**) {

    auto fun_ptr = task1;
    Tasking::Task task(fun_ptr, &args);
    //task1.start();
    //task1.join();
    return 0;
}
