#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;

void printMessage(const string& message, int count) {
    for (int i = 0; i < count; ++i) {
        cout << message << " (iteration " << i + 1 << ")" << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main() {
    thread t1(printMessage, "Thread 1: Hello from thread 1", 5);
    thread t2(printMessage, "Thread 2: Greetings from thread 2", 5);

    thread t3([]() {
        for (int i = 0; i < 5; ++i) {
            cout << "Thread 3: Lambda thread running (iteration " << i + 1 << ")" << endl;
            this_thread::sleep_for(chrono::milliseconds(100));
        }
        });

    t1.join();
    t2.join();
    t3.join();

    cout << "All threads have finished execution." << endl;

    return 0;
}
