#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5 // number of philosophers
#define THINKING 0
#define HUNGRY 1
#define EATING 2

using namespace std;

int state[N];           // philosopher states
pthread_mutex_t mutex;  // single mutex lock
pthread_cond_t cond[N]; // one condition variable per philosopher

void test(int i)
{
    int left = (i + N - 1) % N;
    int right = (i + 1) % N;

    if (state[i] == HUNGRY &&
        state[left] != EATING &&
        state[right] != EATING)
    {
        state[i] = EATING;
        pthread_cond_signal(&cond[i]);
    }
}
void pickup_chopsticks(int i)
{
    pthread_mutex_lock(&mutex);

    state[i] = HUNGRY;
    test(i);

    while (state[i] != EATING)
        pthread_cond_wait(&cond[i], &mutex);

    pthread_mutex_unlock(&mutex);
}
void putdown_chopsticks(int i)
{
    pthread_mutex_lock(&mutex);
    cout << "Philosopher " << i << " has finished eating and is putting down chopsticks." << endl;

    state[i] = THINKING;

    int left = (i + N - 1) % N;
    int right = (i + 1) % N;

    test(left);
    test(right);

    pthread_mutex_unlock(&mutex);
}
void *philosopher(void *num)
{
    int id = *(int *)num;
    while (1)
    {
        cout << "Philosopher " << id << " is thinking." << endl;
        sleep(1);
        cout << "Philosopher " << id << " is hungry and trying to pick up chopsticks." << endl;

        pickup_chopsticks(id);
        cout << "Philosopher " << id << " is eating." << endl;

        sleep(1);
        putdown_chopsticks(id);
    }
    return NULL;
}

int main()
{
    pthread_t threads[N];
    int ids[N];
    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < N; i++)
    {
        pthread_cond_init(&cond[i], NULL);
        ids[i] = i;
        state[i] = THINKING;
    }
    for (int i = 0; i < N; i++)
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    for (int i = 0; i < N; i++)
        pthread_join(threads[i], NULL);
    return 0;
}