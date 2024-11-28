#include <iostream>
#include <thread>
#include <string>
#include <mutex>
using namespace std;

mutex m;
int bank_account_sum = 0;

void modify_bank_account(int modify, int repeat)
{
    for(int i=0; i<repeat; i++)
    {
        lock_guard<mutex> l(m);
        bank_account_sum += modify;
    }
}

int main()
{
    thread thread1(modify_bank_account, +1, 1000000);
    thread thread2(modify_bank_account, -1, 1000000);
    
    thread1.join();
    thread2.join();
    
    return 0;
}
