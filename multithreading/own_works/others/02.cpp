#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

mutex m;
condition_variable cv;

int sharedData = 0; 
bool isReady = false;

void incrementData() {
    this_thread::sleep_for(chrono::seconds(1));

    unique_lock<mutex> lock(m);
    isReady = true;

    for (int i = 0; i < 100; i++) {
        sharedData += 2;
    }

    cout << "Shared data increased to " << sharedData << endl;

    cv.notify_one();
}

void decrementData() {
    unique_lock<mutex> lock(m);
    cv.wait(lock, [] { return isReady; }); 

    for (int i = 0; i < 100; i++) {
        sharedData--;
    }

    cout << "Shared data decreased to: " << sharedData << endl;
}

int main() {
    thread producer(incrementData);
    thread consumer(decrementData);

    producer.join();
    consumer.join();

    system("pause>nul");
}
