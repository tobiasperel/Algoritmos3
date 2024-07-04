#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>
#include <vector>

using namespace std;

#define MAX_SIZE 20  // Adjust based on maximum grid size

enum LocationType { WATER, ICE, LARGE_WOOD, SAFE_ZONE };

struct Location {
  LocationType type;
  int capacity; // Maximum people it can hold (0 for water)
  bool visited;
};

bool bfs(int rGraph[MAX_SIZE][MAX_SIZE], int s, int t, int parent[]) {
  bool visited[MAX_SIZE];
  memset(visited, 0, sizeof(visited));

  queue<int> q;
  q.push(s);
  visited[s] = true;
  parent[s] = -1;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v = 0; v < MAX_SIZE; v++) {
      if (visited[v] == false && rGraph[u][v] > 0) {
        if (v == t) {
          parent[v] = u;
          return true;
        }
        q.push(v);
        parent[v] = u;
        visited[v] = true;
      }
    }
  }

  return false;
}

int fordFulkerson(Location grid[MAX_SIZE][MAX_SIZE], int X, int Y, int P) {
  int source = 0;
  int sink = X * Y + 1; // Last node as sink

  int rGraph[MAX_SIZE][MAX_SIZE];
  memset(rGraph, 0, sizeof(rGraph));

  for (int i = 0; i < X; ++i) {
    for (int j = 0; j < Y; ++j) {
      int node = i * Y + j; // Unique node id for the grid
      switch (grid[i][j].type) {
        case WATER:
          break;
        case ICE:
        case LARGE_WOOD:
          rGraph[node][node + 1] = 1; // Flow of 1 for movement
          if (grid[i][j].type == LARGE_WOOD) {
            rGraph[source][node] = P; // Capacity of large wood
          }
          break;
        case SAFE_ZONE:
          rGraph[node + 1][sink] = INT_MAX; // Unlimited flow to sink
          break;
      }
    }
  }

  int parent[MAX_SIZE];
  int max_flow = 0;

  while (bfs(rGraph, source, sink, parent)) {
    int path_flow = INT_MAX;
    int u;
    for (int v = sink; v != source; v = parent[v]) {
        
      u = parent[v];
      path_flow = min(path_flow, rGraph[u][v]);
    }

    for (int v = sink; v != source; v = parent[v]) {
      u = parent[v];
      rGraph[u][v] -= path_flow;
      rGraph[v][u] += path_flow;
    }

    max_flow += path_flow;
  }

  return max_flow;
}

int main() {
  int X, Y, P;
  cin >> X >> Y >> P;

  Location grid[MAX_SIZE][MAX_SIZE];

  // Read the grid data and populate location types and capacities
  for (int i = 0; i < X; ++i) {
    for (int j = 0; j < Y; ++j) {
      char ch;
      cin >> ch;
      switch (ch) {
        case '~':
          grid[i][j] = {WATER, 0, false};
          break;
        case '.':
          grid[i][j] = {ICE, 0, false};
          break;
        case '@':
          grid[i][j] = {LARGE_WOOD, P, false};
          break;
        case '#':
          grid[i][j] = {SAFE_ZONE, INT_MAX, false};
          break;
        default:
          cerr << "Invalid character: " << ch << endl;
          exit(1);
      }
    }
  }

  // Find the maximum number of survivors
  int max_survivors = fordFulkerson(grid, X, Y, P);

  // Print the maximum number of survivors
  cout << max_survivors << endl;

  return 0;
}