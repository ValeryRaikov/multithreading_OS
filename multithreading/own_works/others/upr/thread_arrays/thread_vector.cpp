#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

using namespace std;

int sharedData = 0;
mutex m;

void incrementSharedData(int value) {
	lock_guard<mutex> lock(m);
	sharedData += value;
	cout << "Incrementing -> " << sharedData << endl;
}

void decrementSharedData(int value) {
	lock_guard<mutex> lock(m);
	sharedData -= value;
	cout << "Decrementing -> " << sharedData << endl;
}

int main() {
	// vector of threads!
	vector<thread> threadsArr;
	int inc = 3, dec = 1;

	cout << "Creating the threads!\n";
	for (int i = 0; i < 5; ++i) { // assume 5 is received dynamically...
		if (i & 1) {
			threadsArr.emplace_back(incrementSharedData, inc);
			inc++;
			this_thread::sleep_for(chrono::milliseconds(500));
		}
		else {
			threadsArr.emplace_back(decrementSharedData, dec);
			dec++;
			this_thread::sleep_for(chrono::milliseconds(500));
		}
	}

	for (auto& th : threadsArr) {
		th.join();
	}

	cout << "Finished!\n";
	cout << "Inc value: " << inc << "\nDec value: " << dec << endl;

	system("pause>nul");
}