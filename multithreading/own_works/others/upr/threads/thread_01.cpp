#include <iostream>
#include <thread>
#include <string>
using namespace std;

void print_in_thread(string msg, int repeat)
{
    for(int i=0; i<repeat; i++)
        cout<<msg<<endl;
}

int main()
{
    thread static_thread(print_in_thread,"Thread 1", 100);
    thread* dynamic_thread = new thread(print_in_thread, "Thread 2", 100);
    thread lambda_example([](string msg, int repeat){
        for(int i=0; i<repeat; i++)
            cout<<msg<<endl;
    },"Thread 3", 100);


    static_thread.join();
    dynamic_thread->join();
    lambda_example.join();

    delete dynamic_thread;
    
    return 0;
}
