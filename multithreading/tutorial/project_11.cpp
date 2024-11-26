#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex m1, m2;

void taskA() {
	for (int i = 0; i < 100; i++) {
		lock(m1, m2);
		cout << "Task A\n";
		m1.unlock();
		m2.unlock();
	}
}

void taskB() {
	for (int i = 0; i < 100; i++) {
		lock(m2, m1);
		cout << "Task B\n";
		m2.unlock();
		m1.unlock();
	}
}

int main() {
	thread th1(taskA);
	thread th2(taskB);

	th1.join();
	th2.join();

	system("pause>nul");
}