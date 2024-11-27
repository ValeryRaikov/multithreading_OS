#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex mutexPool;
int currentPoolCapacity = 0;
const int maxPoolCapacity = 5000;

void threadFunction(int updateVolume, int sleepInMilliseconds) {
	bool sleepFlag = false;

	while (true) {
		mutexPool.lock();
		if ((currentPoolCapacity + updateVolume > maxPoolCapacity) || (currentPoolCapacity + updateVolume < 0)) {
			sleepFlag = true;
		} else {
			currentPoolCapacity += updateVolume;
		}
		mutexPool.unlock();

		if (sleepFlag) {
			this_thread::sleep_for(chrono::seconds(10));
			sleepFlag = false;
		} else {
			this_thread::sleep_for(chrono::milliseconds(sleepInMilliseconds));
		}
	}
}

int main() {
	int timeRunning = 0;
	thread *th1, *th2, *th3;
	th1 = new thread(threadFunction, 10, 30);
	th2 = new thread(threadFunction, -50, 70);
	th3 = new thread(threadFunction, -300, 1000);

	while (true) {
		mutexPool.lock();
		cout << "Time " << timeRunning << " -> Pool Capacity: " << currentPoolCapacity << endl;
		mutexPool.unlock();
		timeRunning++;
		this_thread::sleep_for(chrono::seconds(1));
	}

	th1->join();
	th2->join();
	th3->join();

	system("pause>nul");
}