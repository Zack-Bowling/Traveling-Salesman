/*
Zackary Bowling
Original Algorithm
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <limits>

using namespace std;

//begin heuristic
int heuristic(const vector<vector<int>>& graph, vector<int>& path) {
    int numCities = graph.size(); //get the number of cities

    vector<bool> visited(numCities, false); //boolean to mark cities as visited
    int currentCity = 0; //start from the first city
    path.push_back(currentCity); //add starting city to path
    visited[currentCity] = true; //mark city as visited
    int totalDistance = 0; //initialize total distance

    //iterate over all cities
    for (int i = 0; i < numCities - 1; ++i) {
        int nearestCity = -1; //variable to store the index of nearest unvisited city
        double maxReciprocal = numeric_limits<double>::min(); //maximum reciprocal is minimum double value

        //find the nearest unvisited city
        for (int j = 0; j < numCities; ++j) {
            if (!visited[j] && j != currentCity) { //exclude current city
                double reciprocalDistance = 1.0 / static_cast<double>(graph[max(currentCity, j)][min(currentCity, j)]);
                if (reciprocalDistance > maxReciprocal) {
                    maxReciprocal = reciprocalDistance;
                    nearestCity = j;
                }
            }
        }

        //move to the nearest unvisited city
        currentCity = nearestCity;
        path.push_back(currentCity); //add nearest city to path
        visited[currentCity] = true; //mark city as visited
        totalDistance += 1.0 / maxReciprocal; //update total distance
    }

    //return to the start city to complete the tour
    totalDistance += 1.0 / static_cast<double>(graph[path.back()][0]); //add distance from last city to start city
    path.push_back(0); //add the start city again to complete the cycle

    return static_cast<int>(totalDistance);
}

//function to read graph from a file 
vector<vector<int>> readGraph(const string& filename) {
    vector<vector<int>> graph;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file " << filename << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        vector<int> row;
        int distance;
        while (ss >> distance) {
            row.push_back(distance);
        }
        graph.push_back(row);
    }

    file.close();
    return graph;
}

int main() {
    string filename = "graph1000.graph";
    vector<vector<int>> graph = readGraph(filename);

    //perform heuristic algorithm
    vector<int> tour; //empty vector to store the tour
    int totalDistance = heuristic(graph, tour);

    //output the tour
    cout << "Solution: ";
    for (int city : tour) {
        cout << city << " ";
    }
    cout << "\nDistance: " << totalDistance << endl;

    return 0;
}
