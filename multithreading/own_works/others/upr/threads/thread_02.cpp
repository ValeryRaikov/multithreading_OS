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
        m.lock();
        bank_account_sum += modify;
        m.unlock();

        //m.try_lock()
        //1 - if locked from us, 0 - if is already locked
    }
}

int main()
{
    thread thread1(modify_bank_account, +1, 1000000);
    thread thread2(modify_bank_account, -1, 1000000);
    
    thread1.join();
    thread2.join();

    cout<<"Bank account:    " << bank_account_sum<<endl;

    return 0;
}
