#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void foo() {
	cout << "Thread 1 ";
}

void bar(int x) {
	this_thread::sleep_for(chrono::seconds(2));
	cout << "Thread 2 " << x << "   ";
}

int main() {
	thread th1(foo);
	thread th2(bar, 30);

	cout << "main, foo and bar now execute concurently...\n";

	th1.join();
	th2.join();

	system("pause>nul");
}