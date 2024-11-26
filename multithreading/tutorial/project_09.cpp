// Deadlock

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex m1;
mutex m2;

void thread1() {
	m1.lock();
	this_thread::sleep_for(chrono::seconds(1));
	m2.lock();
	cout << "Critical section of Thread Thread One!\n";
	m1.unlock();
	m2.unlock();
}

/*
void thread2() { // Simulating deadlock situation
	m2.lock();
	this_thread::sleep_for(chrono::seconds(1));
	m1.lock();
	cout << "Critical section of Thread Thread Two!\n";
	m2.unlock();
	m1.unlock();
}
*/

void thread2() {
	m1.lock();
	this_thread::sleep_for(chrono::seconds(1));
	m2.lock();
	cout << "Critical section of Thread Thread Two!\n";
	m2.unlock();
	m1.unlock();
}

int main() {
	thread th1(thread1);
	thread th2(thread2);

	th1.join();
	th2.join();

	system("pause>nul");
}