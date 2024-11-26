#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int bankBalance = 15000;
mutex m;

class User {
private:
	int userId;
	int cardInitAmount;
public:
	User(int userId, int cardInitAmount) {
		this->userId = userId;
		this->cardInitAmount = cardInitAmount;
	}

	int getUserId() { return userId; }
	int getCardInitAmount() { return cardInitAmount; }

	void depositMoney(int amount) {
		lock_guard<mutex> lock(m);
		cardInitAmount += amount;
		bankBalance += amount;
		cout << "User " << getUserId() << " deposited " << amount << " and now has total of " << cardInitAmount << endl;
	}

	void withdrawMoney(int amount) {
		lock_guard<mutex> lock(m);
		if (cardInitAmount > amount) {
			cardInitAmount -= amount;
			bankBalance -= amount;
			cout << "User " << getUserId() << " successfully withdrew " << amount << " and now has total of " << cardInitAmount << endl;
		} else {
			cout << "User " << getUserId() << " has insufficient funds. Withdraw failed!\n";
		}
	}

	friend ostream& operator<<(ostream& os, const User& user) {
		os << "User" << user.userId << " -> " << user.cardInitAmount << endl;

		return os;
	}
};

void user1Actions() {
	User user1(1, 1000);
	user1.depositMoney(500);
	this_thread::sleep_for(chrono::seconds(1));
	user1.withdrawMoney(700);
	this_thread::sleep_for(chrono::seconds(1));
	user1.withdrawMoney(1000);
	this_thread::sleep_for(chrono::seconds(1));

	cout << user1;
}

void user2Actions() {
	User user2(2, 0);
	user2.depositMoney(300);
	this_thread::sleep_for(chrono::seconds(1));
	user2.withdrawMoney(100);
	this_thread::sleep_for(chrono::seconds(1));
	user2.withdrawMoney(200);
	this_thread::sleep_for(chrono::seconds(1));

	cout << user2;
}

void user3Actions() {
	User user3(3, 550);
	user3.depositMoney(450);
	this_thread::sleep_for(chrono::seconds(1));
	user3.withdrawMoney(1000);
	this_thread::sleep_for(chrono::seconds(1));
	user3.withdrawMoney(500);
	this_thread::sleep_for(chrono::seconds(1));

	cout << user3;
}

int main() {
	thread user1Thread(user1Actions);
	thread user2Thread(user2Actions);
	thread user3Thread(user3Actions);

	user1Thread.join();
	user2Thread.join();
	user3Thread.join();

	cout << "Bank balance: " << bankBalance << endl;

	system("pause>nul");
}