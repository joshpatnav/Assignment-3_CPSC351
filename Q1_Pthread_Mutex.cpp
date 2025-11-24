/*
This program is meant to increment the global var across 10 threads with the protection from mutex
Compile: g++ -std=c++17 -pthread -O2 Q1_Pthread_Mutex.cpp -o with_mutex
Run: ./with_mutex
*/
#include <iostream>
#include <pthread.h>

const int THREADS = 10;
const int ITERS = 100000;

int counter = 0; // Global Var
pthread_mutex_t lock;

void * worker(void* arg) {
    (void)arg;
    for (int i = 0; i < ITERS; i++) 
    {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t threads[THREADS];

    pthread_mutex_init(&lock, NULL);

    //Create 10 threads
    for (int i = 0; i < THREADS; i++) pthread_create(&threads[i], NULL, worker, NULL);
    //Each thread increments
    for (int i = 0; i < THREADS; i++) pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&lock);

    std::cout << "Final counter(With Mutex): " << counter << " (expected " << THREADS * ITERS << ")\n";

    return 0;
}