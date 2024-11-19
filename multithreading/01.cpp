#include <iostream>
#include <thread>

using namespace std;

void function1(char symbol) {
	for (int i = 0; i < 100; i++) {
		cout << symbol;
	}
}

int main() {
	thread th1(function1, 'x');
	thread th2(function1, 'y');

	system("pause>nul");
}
