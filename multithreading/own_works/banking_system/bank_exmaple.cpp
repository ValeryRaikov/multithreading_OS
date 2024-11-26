/*
// using simple mutex lock
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

int bankBalance = 10000;
mutex m;
bool isBankrupt = false;

void depositMoney(int userId, int amount) {
    m.lock(); 
    bankBalance += amount;
    cout << "User " << userId << " deposited " << amount << ". Balance increased to " << bankBalance << endl;
    m.unlock(); 
}

void withdrawMoney(int userId, int amount) {
    m.lock(); 
    if (bankBalance >= amount) {
        bankBalance -= amount;
        cout << "User " << userId << " withdrew " << amount << ". Balance: " << bankBalance << endl;
    }
    else {
        cout << "User " << userId << " attempted to withdraw " << amount << " but insufficient funds." << endl;
    }

    if (bankBalance <= 0) {
        isBankrupt = true;
        cout << "Bank has gone bankrupt! Stopping all transactions." << endl;
    }
    m.unlock();  
}

// Test functions for user actions
void user1Activity() {
    depositMoney(1, 2000);
    this_thread::sleep_for(chrono::milliseconds(1000));

    withdrawMoney(1, 1500);
    this_thread::sleep_for(chrono::milliseconds(1000));

    withdrawMoney(1, 3000);
}

void user2Activity() {
    withdrawMoney(2, 1000);
    this_thread::sleep_for(chrono::milliseconds(1000));

    depositMoney(2, 5000);
    this_thread::sleep_for(chrono::milliseconds(1000));

    withdrawMoney(2, 3000);
}

void user3Activity() {
    depositMoney(3, 3000);
    this_thread::sleep_for(chrono::milliseconds(1000));

    withdrawMoney(3, 25000);
    this_thread::sleep_for(chrono::milliseconds(1000));
}

void user4Activity() {
    withdrawMoney(4, 2000);
    this_thread::sleep_for(chrono::milliseconds(1000));

    withdrawMoney(4, 7000);
}

int main() {
    thread user1(user1Activity);
    thread user2(user2Activity);
    thread user3(user3Activity);
    thread user4(user4Activity);

    user1.join();
    user2.join();
    user3.join();
    user4.join();

    cout << "Simulation complete. Final balance: " << bankBalance << endl;

    return 0;
}
*/


// using unique_lock and condition_variable
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

int bankBalance = 10000;
mutex m;
condition_variable cv;
bool isBankrupt = false;

void depositMoney(int userId, int amount) {
	unique_lock<mutex> lock(m);
	bankBalance += amount;
	cout << "User " << userId << " deposited " << amount << ". Balanced increased to " << bankBalance << endl;
	cv.notify_all(); // notify all other threads
}

void withdrawMoney(int userId, int amount) {
	unique_lock<mutex> lock(m);
	if (bankBalance >= amount) {
		bankBalance -= amount;
		cout << "User " << userId << " withdrew " << amount << ". Balance: " << bankBalance << endl;
	} else {
		cout << "User " << userId << " attempted to withdraw " << amount << " but insufficient funds." << endl;
	}

	if (bankBalance <= 0) {
		isBankrupt = true;
		cout << "Bank has gone bankrupt! Stopping all transactions." << endl;
		cv.notify_all();
	}
}

// test functions for user actions
void user1Activity() {
    depositMoney(1, 2000);
    this_thread::sleep_for(chrono::milliseconds(1000));

    withdrawMoney(1, 1500);
    this_thread::sleep_for(chrono::milliseconds(1000));

    withdrawMoney(1, 3000);
}

void user2Activity() {
    withdrawMoney(2, 1000);
    this_thread::sleep_for(chrono::milliseconds(1000));

    depositMoney(2, 5000);
    this_thread::sleep_for(chrono::milliseconds(1000));

    withdrawMoney(2, 3000);
}

void user3Activity() {
    depositMoney(3, 3000);
    this_thread::sleep_for(chrono::milliseconds(1000));

    withdrawMoney(3, 25000);
    this_thread::sleep_for(chrono::milliseconds(1000));
}

void user4Activity() {
    withdrawMoney(4, 2000);
    this_thread::sleep_for(chrono::milliseconds(1000));

    withdrawMoney(4, 7000);
}

int main() {
	thread user1(user1Activity);
	thread user2(user2Activity);
	thread user3(user3Activity);
	thread user4(user4Activity);

	user1.join();
	user2.join();
	user3.join();
	user4.join();

	cout << "Simulation complete. Final balance: " << bankBalance << endl;

	system("pause>nul");
}