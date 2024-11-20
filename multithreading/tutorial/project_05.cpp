#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

int X = 0, Y = 0;
mutex m1, m2;

void doSomeWorkForSeconds(int seconds) {
	this_thread::sleep_for(chrono::seconds(seconds));
}

void incrementXandY(int& XorY, mutex& m, const char* desc) {
	for (int i = 0; i < 5; i++) {
		m.lock();

		XorY++;
		cout << desc << " = " << XorY << endl;

		m.unlock();
		doSomeWorkForSeconds(1);
	}
}

void consumeXY() {
	int useCount = 5;
	int XplusY = 0;

	while (true) {
		int lockResult = try_lock(m1, m2);

		if (lockResult == -1) {
			if (X != 0 && Y != 0) {
				useCount--;
				XplusY += X + Y;
				X = 0;
				Y = 0;
				cout << "XplusY = " << XplusY << endl;
			}

			m1.unlock();
			m2.unlock();

			if (useCount == 0)
				break;
		}
	}
}

int main() {
	thread th1(incrementXandY, ref(X), ref(m1), "X");
	thread th2(incrementXandY, ref(Y), ref(m2), "Y");
	thread th3(consumeXY);

	th1.join();
	th2.join();
	th3.join();

	system("pause>nul");
}