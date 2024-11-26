// promise and future

#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <future>

using namespace std;

typedef long int ull;

void findOdd(promise<ull>&& oddSumPromise, ull start, ull end) {
	ull oddSum = 0;
	for (ull i = start; i <= end; i++) {
		if (i & 1) {
			oddSum += i;
		}
	}

	oddSumPromise.set_value(oddSum);
}

int main() {
	ull start = 0;
	ull end = 1900000000;

	promise<ull> oddSum;
	future<ull> oddFuture = oddSum.get_future();

	cout << "Thread Created!\n";
	thread th1(findOdd, move(oddSum), start, end);

	cout << "Waiting for result!\n";
	cout << "Odd Sum is: " << oddFuture.get() << endl;
	cout << "Completed!\n";

	th1.join();

	system("pause>nul");
}