#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void run(int count) {
	while (count-- > 0) {
		cout << count << endl;
	}

	this_thread::sleep_for(chrono::seconds(3));
	cout << "Thread finished!" << endl;
}

int main() {
	thread th1(run, 10);
	cout << "main()" << endl;

	// if (th1.joinable())
	//	  th1.join();

	if (th1.joinable())
		th1.detach();

	cout << "main() after" << endl;

	system("pause>nul");
}