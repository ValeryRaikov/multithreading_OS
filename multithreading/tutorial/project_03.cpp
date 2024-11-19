#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int amount = 0;
mutex m;

void addMoney() {
	m.lock();
	amount++;
	m.unlock();
}

int main() {
	thread th1(addMoney);
	thread th2(addMoney);

	th1.join();
	th2.join();

	cout << "Amount: " << amount << endl;

	system("pause>nul");
}