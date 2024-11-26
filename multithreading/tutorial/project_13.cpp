// async

#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <future>

using namespace std;

typedef long int ull;

ull findOdd(ull start, ull end) {
	ull oddSum = 0;
	for (ull i = start; i <= end; i++) {
		if (i & 1) {
			oddSum += i;
		}
	}

	return oddSum;
}

int main() {
	ull start = 0;
	ull end = 1900000000;

	cout << "Thread Created!\n";
	future<ull> oddFuture = async(launch::deferred, findOdd, start, end);

	cout << "Waiting for result!\n";
	cout << "Odd Sum is: " << oddFuture.get() << endl;
	cout << "Completed!\n";

	system("pause>nul");
}