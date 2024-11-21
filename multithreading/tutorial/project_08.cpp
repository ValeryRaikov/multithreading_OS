#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

condition_variable cv;
mutex m;
long balance = 0;

void addMoney(int money) {
	lock_guard<mutex> lg(m);

	balance += money;
	cout << "Amount added. Current balance: " << balance << endl;
	cv.notify_one();
}

void withdrawMoney(int money) {
	unique_lock<mutex> ul(m);

	cv.wait(ul, [] { return (balance != 0) ? true : false; });
	if (balance >= money) {
		balance -= money;
		cout << "Amount deduced: " << money << endl;
	} else {
		cout << "Amount cannot be deduced, current balance is less than " << money << endl;
	}

	cout << "Current balance is: " << balance << endl;
}

int main() {
	thread th1(withdrawMoney, 500);
	thread th2(addMoney, 500);

	th1.join();
	th2.join();

	system("pause>nul");
}