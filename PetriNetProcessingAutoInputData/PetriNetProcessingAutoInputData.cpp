#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <set>
#include <ctime>

using namespace std;

// Function to generate a random 2-digit number
int generateRandom2DigitNumber(int routeNumber) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(10, 99); // 2-digit range
	return (routeNumber * 100) + dist(gen);
}

int main() {
	int totalInRoutes;
	srand(time(0)); // Seed the random number generator with the current time
	totalInRoutes = rand() % 8 + 1; // Randomly choose the number of "in" routes (1 to 9)
	int totalOutRoutes;
	totalOutRoutes = rand() % 8 + 1; // Randomly choose the number of "out" routes (1 to 9)

	cout << endl;

	cout << "Total 'in' routes generated: " << totalInRoutes << endl;
	cout << "Total 'out' routes generated: " << totalOutRoutes << endl;

	// Create vectors to store the number of vehicles for "in" and "out" routes
	vector<int> vehiclesInPerRoute(totalInRoutes);
	vector<vector<int>> vehiclesOutPerRoute(totalOutRoutes);

	// Generate random 2-digit numbers for vehicles in "in" routes
	vector<int> allVehicles;
	int totalVehiclesIn = 0; // Total vehicles in "in" routes
	for (int inRoute = 0; inRoute < totalInRoutes; inRoute++) {
		int numVehicles = rand() % 98 + 1; // Randomly choose the number of vehicles (1 to 99) for each route
		vehiclesInPerRoute[inRoute] = numVehicles;
		totalVehiclesIn += numVehicles;
		for (int i = 0; i < numVehicles; i++) {
			int vehicleNumber = generateRandom2DigitNumber(inRoute + 1);
			allVehicles.push_back(vehicleNumber);
		}
		cout << "'in' Route " << (inRoute + 1) << ": " << vehiclesInPerRoute[inRoute] << " vehicles" << endl;
	}

	// Shuffle all vehicles randomly
	random_shuffle(allVehicles.begin(), allVehicles.end());

	// Distribute vehicles to "out" routes randomly
	for (int i = 0; i < totalVehiclesIn; i++) {
		int outRoute = rand() % totalOutRoutes; // Pick a random "out" route
		vehiclesOutPerRoute[outRoute].push_back(allVehicles[i]);
	}

	cout << endl;

	// Display the resulting data for "out" routes and calculate the total for each "out" route
	cout << "Vehicles passed from 'out' routes:\n" << endl;
	vector<int> totalVehiclesPassed(totalOutRoutes, 0);
	for (int outRoute = 0; outRoute < totalOutRoutes; outRoute++) {
		cout << "\n'out' Route " << (outRoute + 1) << " Vehicles: ";
		for (int i = 0; i < vehiclesOutPerRoute[outRoute].size(); i++) {
			cout << vehiclesOutPerRoute[outRoute][i] << " ";
			totalVehiclesPassed[outRoute]++;
		}
		cout << "\n (Total: " << totalVehiclesPassed[outRoute] << ")" << endl;
	}

	cout << endl;

	// Calculate the total number of vehicles passed through "out" routes
	int totalVehiclesOut = totalVehiclesIn;

	// Display the totals
	cout << "Total number of vehicles in 'in' routes: " << totalVehiclesIn << endl;
	cout << "Total number of vehicles passed through 'out' routes: " << totalVehiclesOut << endl;

	cout << endl;

	return 0;
}
