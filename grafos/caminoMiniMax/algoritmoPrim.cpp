#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Edge {
    int u, v, weight;
    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};

bool operator<(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

vector<Edge> edges;
vector<bool> visited;
vector<int> parent;

void prim(int n) {
    priority_queue<Edge> pq;
    visited.assign(n, false);
    parent.assign(n, -1);

    pq.push(Edge(0, 0, 0)); // Start from node 0

    while (!pq.empty()) {
        Edge current = pq.top();
        pq.pop();

        int u = current.u;

        if (visited[u]) {
            continue;
        }

        visited[u] = true;

        if (current.u != 0) {
            cout << current.u << " " << current.v << endl;
        }

        for (int i = 0; i < edges.size(); i++) {
            Edge edge = edges[i];
            int v = edge.v;
            int weight = edge.weight;

            if (!visited[v] && weight < current.weight) {
                parent[v] = u;
                pq.push(Edge(v, v, weight));
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m; // Number of nodes and edges

    for (int i = 0; i < m; i++) {
        int u, v, weight;
        cin >> u >> v >> weight; // Input edges and weights
        edges.push_back(Edge(u, v, weight));
    }

    prim(n); // Apply Prim's algorithm
    

    return 0;
}
