#pragma once
#include <pthread.h>

namespace Threading
{
    class Thread{
        private:
            pthread_t thread;
            int id;
            enum class Thread_State{
                OK,
                FAIL,
                IN_PROGRESS,
                PAUSED,
                COMPLETED,
                DEFAULT
            };
        public:
            Thread()
            {

            }
    };

}
