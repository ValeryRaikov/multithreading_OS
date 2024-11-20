#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int counter = 0;
int counter2 = 0;
mutex m;

void increaseCounter() {
	for (int i = 0; i < 10000; i++) {
		if (m.try_lock()) {
			counter++;
			m.unlock();
		}
	}
}

int main() {
	thread th1(increaseCounter);
	thread th2(increaseCounter);

	thread th3([]() {
		for (int i = 0; i < 10000; i++) {
			m.lock();
			counter2++;
			m.unlock();
		}
	});

	thread th4([]() {
		for (int i = 0; i < 10000; i++) {
			m.lock();
			counter2++;
			m.unlock();
		}
	});

	th1.join();
	th2.join();

	th3.join();
	th4.join();

	cout << "Counter is increased to: " << counter << endl;
	cout << "Counter2 is increased to: " << counter2 << endl;

	system("pause>nul");
}