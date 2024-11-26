#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

vector<string> books = {"Book1", "Book2", "Book3", "Book4", "Book5"};
mutex m;

void loanBook(string title) {
	lock_guard<mutex> lock(m);

    if (books.empty()) {
        cout << "Library has no books left!\n";
        return;
    }

    auto it = find(books.begin(), books.end(), title);
    if (it != books.end()) {
        books.erase(it);
        cout << "Book \"" << title << "\" is loaned.\n";
    } else {
        cout << "Book \"" << title << "\" is not found in the library.\n";
    }
}

void returnBook(string title) {
    lock_guard<mutex> lock(m);
    if (find(books.begin(), books.end(), title) == books.end()) {
        books.push_back(title);
        cout << "Book \"" << title << "\" has been returned to the library.\n";
    } else {
        cout << "Book \"" << title << "\" is already in the library.\n";
    }
}

void user1Actions() {
    loanBook("Book1");
    this_thread::sleep_for(chrono::seconds(1));
    loanBook("Book2");
    this_thread::sleep_for(chrono::seconds(1));
    returnBook("Book1");
}

void user2Actions() {
    loanBook("Book1");
    this_thread::sleep_for(chrono::seconds(1));
    loanBook("Book2");
    this_thread::sleep_for(chrono::seconds(1));
    loanBook("Book3");
    this_thread::sleep_for(chrono::seconds(1));
    returnBook("Book1");
}

void user3Actions() {
    loanBook("Book3");
    this_thread::sleep_for(chrono::seconds(1));
    returnBook("Book3");
    this_thread::sleep_for(chrono::seconds(1));
    loanBook("Book4");
    this_thread::sleep_for(chrono::seconds(1));
    loanBook("Book7");
}

void printBooks() {
    for (const auto& book : books) {
        cout << "Book -> " << book << endl;
    }
}

int main() {
    cout << "Initial library books\n";
    printBooks();

    cout << endl;

    thread th1(user1Actions);
    thread th2(user2Actions);
    thread th3(user3Actions);

    th1.join();
    th2.join();
    th3.join();

    cout << "\nLibrary is left with the following books\n";
    printBooks();

	system("pause>nul");
}