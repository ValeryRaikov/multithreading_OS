#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex CarMutex;

void driveCar(string driverName) {
	unique_lock<mutex> carLock(CarMutex);
	cout << driverName << " is driving!" << endl;

	this_thread::sleep_for(chrono::seconds(2));

	cout << driverName << " is done driving!" << endl;
	carLock.unlock();
}

int main() {
	thread th1(driveCar, "Valery");
	thread th2(driveCar, "Magdalena");

	th1.join();
	th2.join();

	system("pause>nul");
}