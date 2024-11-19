#include <iostream>
#include <thread>
#include <map>

using namespace std;

void refreshForecast(map<string, int> forecastMap) {
	while (true) {
		for (auto& item : forecastMap) {
			item.second++;
			cout << item.first << " - " << item.second << endl;
		}

		this_thread::sleep_for(2000ms);
	}
}

int main() {
	map<string, int> forecastMap = {
		{"New York", 15},
		{"Sofia", 8},
		{"Paris", 6},
	};

	thread thBgWorker(refreshForecast, forecastMap);

	system("pause>nul");
}
