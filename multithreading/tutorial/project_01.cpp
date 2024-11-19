// Function pointers

#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>

using namespace std;

typedef unsigned long long ull;

ull oddSum = 0;
ull evenSum = 0;

void findOdd(ull start, ull end) {
	for (ull i = start; i <= end; i++) {
		if ((i & 1) == 1) {
			oddSum += i;
		}
	}
}

void findEven(ull start, ull end) {
	for (ull i = start; i <= end; i++) {
		if ((i & 1) == 0) {
			evenSum += i;
		}
	}
}

int main() {
	ull start = 0, end = 1900000000;

	auto startTime = chrono::high_resolution_clock::now();

	thread th1(findOdd, start, end);
	thread th2(findEven, start, end);

	th1.join();
	th2.join();

	// findOdd(start, end);
	// findEven(start, end);

	auto endTime = chrono::high_resolution_clock::now();
	auto difference = chrono::duration_cast<chrono::microseconds>(endTime - startTime);

	cout << "Odd Sum: " << oddSum << endl;
	cout << "Even Sum: " << evenSum << endl;

	cout << "Execution time: " << difference.count() / 1000000 << 's' << endl;

	system("pause>nul");
}