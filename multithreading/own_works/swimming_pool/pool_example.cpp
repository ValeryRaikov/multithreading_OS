#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

using namespace std;

int poolSize = 10000;
mutex m;

void turnOnPipe(int liters, int pipeId) {
    while (true) {
        bool isPoolEmpty = false;

        {
            lock_guard<mutex> lock(m);
            if (poolSize <= 0) {
                isPoolEmpty = true;
            }
            else {
                poolSize -= liters;
                if (poolSize < 0) poolSize = 0; 
                cout << "Pipe " << pipeId << " drained " << liters
                    << " liters. Pool size: " << poolSize << endl;
            }
        }

        if (isPoolEmpty) break;

        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main() {
    cout << "Starting with full pool: " << poolSize << " liters" << endl;

    vector<thread> pipes;
    pipes.emplace_back(turnOnPipe, 500, 1);
    pipes.emplace_back(turnOnPipe, 300, 2);

    this_thread::sleep_for(chrono::seconds(5));
    pipes.emplace_back(turnOnPipe, 400, 3);

    for (auto& pipe : pipes) {
        pipe.join();
    }

    cout << "Pool is successfully dried up!\n";
    system("pause>nul");
}
