/*
This program is to count the threads without the protection of the mutex
Compile: g++ -std=c++17 -pthread -O2 Q1_Pthread_NoMutex.cpp -o no_mutex
Run: ./no_mutex
*/
#include <iostream>
#include <pthread.h>

const int THREADS = 10;
const int ITERS = 100000;

int counter = 0; // Global Var

void * worker(void* arg) {
    (void)arg;
    for (int i = 0; i < ITERS; ++i) counter++;
    return nullptr;
}

int main() {
    pthread_t tids[THREADS];

    for (int i = 0; i < THREADS; ++i) {
        if(pthread_create(&tids[i], nullptr, worker, nullptr) != 0) {
            std::cerr << "Error creating thread " << i << std::endl;
            return 1;
        }
    }
    
    for (int i = 0; i < THREADS; ++i) {
        pthread_join(tids[i], nullptr);
    }

    std::cout << "Final counter: " << counter << " (expected " << THREADS * ITERS << ")\n";
    return 0;
}