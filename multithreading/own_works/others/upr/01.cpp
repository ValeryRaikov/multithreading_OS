#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex m;

void printBlock(int n, char c) {
	m.lock();
	cout << "Text here " << c << endl;
	for (int i = 0; i < n; ++i) {
		cout << c << ", ";
	}
	cout << endl;
	m.unlock();
}

int main() {
	thread th1(printBlock, 50, '*');
	thread th2(printBlock, 70, '$');

	th1.join();
	th2.join();

	system("pause>nul");
}