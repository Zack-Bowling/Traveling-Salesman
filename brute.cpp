/*
Zackary Bowling
Brute Force
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

//function to read cities from the
vector<vector<double>> readGraph(const string& filename) {
    vector<vector<double>> graph;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "unable to open file " << filename << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        vector<double> row;
        double distance;
        while (ss >> distance) {
            row.push_back(distance);
        }
        graph.push_back(row);
    }

    file.close();

    //fill in upper triangular part
    for (size_t i = 0; i < graph.size(); ++i) {
        for (size_t j = i + 1; j < graph[i].size(); ++j) {
            graph[j][i] = graph[i][j];
        }
    }

    return graph;
}

//brute force algorithm
double bruteForce(const vector<vector<double>>& graph, vector<int>& path) {
    int numCities = graph.size(); // Get the number of cities

    //generate all possible permutations of cities
    vector<int> permutation(numCities);
    for (int i = 0; i < numCities; ++i) {
        permutation[i] = i;
    }

    //calculate total distance for the initial permutation
    double minDistance = numeric_limits<double>::max(); //initialize to a large enough value
    do {
        double totalDistance = 0;
        totalDistance += graph[0][permutation[0]]; //connect city 0 to the first city
        for (int i = 0; i < numCities - 1; ++i) {
            totalDistance += graph[permutation[i]][permutation[i + 1]];
        }
        totalDistance += graph[permutation[numCities - 1]][0]; //connect the last city to city 0
        if (totalDistance < minDistance) {
            minDistance = totalDistance;
            path = permutation;
        }
    } while (next_permutation(permutation.begin(), permutation.end())); //include all elements in permutation

    return minDistance;
}

int main() {
    string filename = "graph15.graph";
    vector<vector<double>> graph = readGraph(filename);

    //perform brute force algorithm
    vector<int> tour; //empty vector to store the tour
    double totalDistance = bruteForce(graph, tour);

    //output the tour
    cout << "Solution: ";
    for (int city : tour) {
        cout << city << " ";
    }
    cout << "\nDistance: " << totalDistance << endl;

    return 0;
}
