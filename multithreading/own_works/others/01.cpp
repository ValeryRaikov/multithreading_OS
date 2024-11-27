#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void displaySymbol(int thId, char symbol) {
	for (int i = 0; i < 100; i++) {
		cout << "Thread " << thId << " -> " << symbol << endl;
		this_thread::sleep_for(chrono::milliseconds(200));
	}
}

int main() {
	thread th1(displaySymbol, 1, 'X');
	thread th2(displaySymbol, 2, 'O');

	th1.join();
	th2.join();

	system("pause>nul");
}