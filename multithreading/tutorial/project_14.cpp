// producer and consumer problem 

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>

using namespace std;

mutex m;
condition_variable cond;
deque<int> buffer;
const unsigned int maxBufferSize = 50;

void producer(int val) {
	while (val) {
		unique_lock<mutex> locker(m);
		cond.wait(locker, []() { return buffer.size() < maxBufferSize; });
		buffer.push_back(val);

		cout << "Produced: " << val << endl;

		val--;
		locker.unlock();
		cond.notify_one(); // notify_all if there are a lot of consumers
	}
}

void consumer() {
	while (1) {
		unique_lock<mutex> locker(m);
		cond.wait(locker, []() { return buffer.size() > 0; });
		int val = buffer.back();
		buffer.pop_back();

		cout << "Consumed: " << val << endl;
		locker.unlock();
		cond.notify_one();
	}
}

int main() {
	thread th1(producer, 100);
	thread th2(consumer);

	th1.join();
	th2.join();

	system("pause>nul");
}