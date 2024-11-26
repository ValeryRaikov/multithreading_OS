#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex m;
long long bankBalance = 0;

void addMoney(long long value) {
	m.lock();
	bankBalance += value;
	m.unlock(); // thread syncronization
}

void withdrawMoney(long long value) {
	m.lock();
	bankBalance -= value;
	m.unlock();
}

int main() {
	thread th1(addMoney, 2000);
	thread th2(addMoney, 10000);
	thread th3(addMoney, 5000);
	thread th4(withdrawMoney, 3500);

	th1.join();
	th2.join();
	th3.join();
	th4.join();

	cout << "Final bank balance is: " << bankBalance << endl;

	system("pause>nul");
}