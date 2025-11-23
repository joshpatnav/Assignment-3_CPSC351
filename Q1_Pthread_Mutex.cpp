/*
This program is meant to count the threads with the mutex protections
Compile: g++ -std=c++17 -pthread -O2 Q1_Pthread_Mutex.cpp -o with_mutex
Run: ./with_mutex
*/
#include <iostream>
#include <pthread.h>

const int THREADS = 10;
const int ITERS = 100000;

int counter = 0; // Global Var
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void * worker(void* arg) {
    (void)arg;
    for (int i = 0; i < ITERS; ++i) 
    {
        pthread_mutex_lock(&counter_mutex);
        counter++;
        pthread_mutex_unlock(&counter_mutex);
    }
    return nullptr;
}

int main() {
    pthread_t threads[THREADS];

    for (int i = 0; i < THREADS; ++i) {
        pthread_create(&threads[i], nullptr, worker, nullptr);
    }
    
    for (int i = 0; i < THREADS; ++i) {
        pthread_join(threads[i], nullptr);
    }

    std::cout << "Final counter(With Mutex): " << counter << " (expected " << THREADS * ITERS << ")\n";

    pthread_mutex_destroy(&counter_mutex);
    return 0;
}