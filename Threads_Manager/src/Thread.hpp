#pragma once
#include <pthread.h>
namespace Threading
{
    class Thread{
        private:
            pthread_t thread;
            void *(*pointer_to_task)(void*);
            int id;
            void* pointer_to_arguments;
        public:
            Thread(void *(*fun_ptr) (void*), void* arg)
            {
                pointer_to_task = fun_ptr;
                pointer_to_arguments = arg;
                state = static_cast<Thread_State>(pthread_create(&thread, nullptr, fun_ptr, arg));
            }

            enum class Thread_State{
                OK,
                FAIL,
                IN_PROGRESS,
                PAUSED,
                COMPLETED,
                DEFAULT
            };

            Thread_State state = Thread_State::DEFAULT;

            Thread_State return_state()
            {
                return state;
            }
    };
}
