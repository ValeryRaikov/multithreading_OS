#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int buffer = 0;
mutex m;

void task(const char* threadNumber, int loopFor) {
	lock_guard<mutex> lock(m);

	for (int i = 0; i < loopFor; i++) {
		buffer++;
		cout << threadNumber << ' ' << buffer << endl;
	}
}

int main() {
	thread th1(task, "T1", 10);
	thread th2(task, "T2", 10);

	th1.join();
	th2.join();

	system("pause>nul");
}