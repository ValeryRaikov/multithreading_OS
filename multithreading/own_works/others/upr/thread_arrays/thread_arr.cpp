#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

const int numThreads = 5;

void doSomeTask(int threadId) {
	cout << "Executing thread " << threadId << endl;
}

int main() {
	thread* threadsArr[numThreads];

	cout << "Creating the threads!\n";
	for (int i = 0; i < numThreads; ++i) {
		threadsArr[i] = new thread(doSomeTask, i + 1);
		this_thread::sleep_for(chrono::milliseconds(500));
;	}

	for (int i = 0; i < numThreads; ++i) {
		threadsArr[i]->join();
		delete threadsArr[i];
	}

	cout << "Finished!\n";

	system("pause>nul");
}