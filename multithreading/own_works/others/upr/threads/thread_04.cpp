#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>
using namespace std;
const int N = 10;
mutex forks[10];
void philosopher(int left_fork, int right_fork)
{
    while(true)
    {
        forks[left_fork].lock();
        forks[right_fork].lock();
        cout<<"Philosopher "<<left_fork<<" is eating"<<endl;
        usleep(100);
        forks[right_fork].unlock();
        forks[left_fork].unlock();
        cout<<"Philosopher "<<left_fork<<" is thinking"<<endl;
        usleep(200);
    }
}

int main()
{
    thread* ph_threads[N];
    for(int i=0; i<N;i++)
    {
        ph_threads[i] = new thread(philosopher, i, (i+1)%N);
    }
    for(int i=0; i<N;i++)
    {
        ph_threads[i]->join();
        delete ph_threads[i];
    }

    return 0;
}
