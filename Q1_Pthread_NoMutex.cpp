/*
This program is meant to increment the global var across 10 threads without the protection from mutex
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
    for (int i = 0; i < ITERS; i++) {
        counter++;
    }
    return NULL;
}

int main() {
    pthread_t threads[THREADS];

    // Create the 10 threads
    for (int i = 0; i < THREADS; i++) pthread_create(&threads[i], NULL, worker, NULL);
    
    // Wait for all of the threads to finish
    for (int i = 0; i < THREADS; i++) pthread_join(threads[i], NULL);

    std::cout << "Final counter(Without Mutex): " << counter << " (expected " << THREADS * ITERS << ")\n";
    return 0;
}