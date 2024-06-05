#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct data {
    int floor;
    int elevator;
    int time;
    
    bool operator>(const data& other) const {
        return time > other.time;
    }
};

int findMinTime(int n, int k, vector<int>& T, vector<vector<int>>& pisos) {
    vector<vector<int>> minTime(n, vector<int>(100, INT_MAX));
    priority_queue<data, vector<data>, greater<data>> pq;

    for (int i = 0; i < n; ++i) {
        if (find(pisos[i].begin(), pisos[i].end(), 0) != pisos[i].end()) {
            minTime[i][0] = 0;
            pq.push({0, i, 0});
        }
    }

    // Algoritmo de Dijkstra
    while (!pq.empty()) {
        data current = pq.top();
        pq.pop();

        int currentFloor = current.floor;
        int currentElevator = current.elevator;
        int currentTime = current.time;

        if (currentTime > minTime[currentElevator][currentFloor]) continue;

        for (int i = 0; i < n; ++i) {
            if (i == currentElevator) {
                for (int nextFloor : pisos[i]) {
                    if (nextFloor != currentFloor) {
                        int nextTime = currentTime + abs(nextFloor - currentFloor) * T[i];
                        if (nextTime < minTime[i][nextFloor]) {
                            minTime[i][nextFloor] = nextTime;
                            pq.push({nextFloor, i, nextTime});
                        }
                    }
                }
            } else {
                if (find(pisos[i].begin(), pisos[i].end(), currentFloor) != pisos[i].end()) {
                    int nextTime = currentTime + 60; // Tiempo para cambiar de ascensor
                    if (nextTime < minTime[i][currentFloor]) {
                        minTime[i][currentFloor] = nextTime;
                        pq.push({currentFloor, i, nextTime});
                    }
                }
            }
        }
    }

    int result = INT_MAX;
    for (int i = 0; i < n; ++i) {
        if (find(pisos[i].begin(), pisos[i].end(), k) != pisos[i].end()) {
            result = min(result, minTime[i][k]);
        }
    }

    return result == INT_MAX ? -1 : result;
}

int main() {
    int n, k;
    while (cin >> n >> k) {
        vector<int> T(n);
        vector<vector<int>> pisos(n);
        for (int i = 0; i < n; ++i){
            cin >> T[i];
        }
        for (int i = 0; i < n; ++i) {
            int piso;
            while (cin >> piso) {
                pisos[i].push_back(piso);
                if (cin.peek() == '\n') break;
            }
        }

        int minTime = findMinTime(n, k, T, pisos);
        if (minTime == -1) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            cout << minTime << endl;
        }
    }
    return 0;
}
