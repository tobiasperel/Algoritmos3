#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int bfs(int numRooms, int numDoors, int numSwitches, int testNum, vector<pair<int, int>>& doorConnections, vector<pair<int, int>>& switchConnections) {
    int totalStates = numRooms * (1 << numRooms);
    vector<vector<int>> adjacencyList(totalStates, vector<int>());

    for (int i = 0; i < numDoors; ++i) {
        int room1 = doorConnections[i].first - 1, room2 = doorConnections[i].second - 1;
        for (int state = 0; state < (1 << numRooms); ++state) {
            int fromState = (room1 << numRooms) + state;
            int toState = (room2 << numRooms) + state;
            if (((fromState >> room1) % 2 == 1) && ((toState >> room2) % 2 == 1)) {
                adjacencyList[fromState].push_back(toState);
                adjacencyList[toState].push_back(fromState);
            }
        }
    }

    for (int i = 0; i < numSwitches; ++i) {
        int room = switchConnections[i].first - 1, switchRoom = switchConnections[i].second - 1;
        for (int state = 0; state < (1 << numRooms); ++state) {
            int fromState = (room << numRooms) + state;
            int toState = fromState ^ (1 << switchRoom);
            adjacencyList[fromState].push_back(toState);
        }
    }

    vector<bool> visited(totalStates, false);
    visited[1] = true;
    queue<int> toVisit;
    toVisit.push(1);
    vector<int> bfsTree(totalStates, -1);
    bool finished = false;

    while (!toVisit.empty() && !finished) {
        int currentState = toVisit.front();
        toVisit.pop();
        for (int nextState : adjacencyList[currentState]) {
            if (!visited[nextState]) {
                visited[nextState] = true;
                bfsTree[nextState] = currentState;
                toVisit.push(nextState);
            }
        }
    }

    int finalState = ((numRooms - 1) << numRooms) + (1 << (numRooms - 1));
    vector<int> path;
    path.push_back(finalState);
    while (finalState != -1 && finalState != 1) {
        finalState = bfsTree[finalState];
        if (finalState != -1)
            path.push_back(finalState);
    }

    int pathLength = path.size();
    cout << "Villa #" << testNum << endl;
    if (pathLength == 0 || path[pathLength - 1] != 1)
        cout << "The problem cannot be solved." << endl;
    else {
        cout << "The problem can be solved in " << pathLength - 1 << " steps:" << endl;
        for (int i = pathLength - 1; i >= 1; i--) {
            int fromState = path[i], toState = path[i - 1];
            if ((fromState >> numRooms) == (toState >> numRooms)) {
                int difference = abs(fromState - toState);
                int room = 0;
                while (difference >>= 1) ++room;
                if (fromState > toState)
                    cout << "- Switch off light in room " << (room + 1) << "." << endl;
                else
                    cout << "- Switch on light in room " << (room + 1) << "." << endl;
            } else {
                cout << "- Move to room " << ((toState >> numRooms) + 1) << "." << endl;
            }
        }
    }
    cout << endl;
    return pathLength;
}

int main() {
    int numRooms, numDoors, numSwitches, testCase = 0;
    while (cin >> numRooms >> numDoors >> numSwitches, numRooms != 0 || numDoors != 0 || numSwitches != 0) {
        vector<pair<int, int>> doorConnections(numDoors);
        vector<pair<int, int>> switchConnections(numSwitches);
        for (int i = 0; i < numDoors; ++i) {
            cin >> doorConnections[i].first >> doorConnections[i].second;
        }
        for (int i = 0; i < numSwitches; ++i) {
            cin >> switchConnections[i].first >> switchConnections[i].second;
        }
        bfs(numRooms, numDoors, numSwitches, ++testCase, doorConnections, switchConnections);
    }
    return 0;
}
