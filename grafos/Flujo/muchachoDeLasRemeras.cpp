// inicialmente edmonds_karp de https://github.com/rabiulcste/graph-theory/blob/master/Max%20Flow%20Edmonds-Karp%20Algorithm.cpp pero despues lo cambie un poco
#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

#define MAXN 100 // maximum no. of nodes in graph
#define INF 2147483646

int capacity[MAXN][MAXN];
int flowPassed[MAXN][MAXN];
vector<int> graph[MAXN];
int parent[MAXN];

bool bfs(int source, int sink, int n) {
    for (int i = 0; i < n; ++i) {
        parent[i] = -1;
    }
    
    queue<int> q;
    q.push(source);
    parent[source] = -2;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : graph[u]) {
            if (parent[v] == -1 && capacity[u][v] - flowPassed[u][v] > 0) {
                parent[v] = u;
                if (v == sink) return true;
                q.push(v);
            }
        }
    }
    return false;
}

int edmonds_karp(int source, int sink, int n) {
    int maxFlow = 0;
    while (bfs(source, sink, n)) {
        int flow = INF;
        int u = sink;

        while (u != source) {
            int v = parent[u];
            flow = min(flow, capacity[v][u] - flowPassed[v][u]);
            u = v;
        }

        u = sink;
        while (u != source) {
            int v = parent[u];
            flowPassed[v][u] += flow;
            flowPassed[u][v] -= flow;
            u = v;
        }

        maxFlow += flow;
    }
    return maxFlow;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int N, M;
        cin >> N >> M;

        int source = 0;
        int sink = N + M + 1;
        int totalNodes = N + M + 2;

        for (int i = 0; i < totalNodes; ++i) {
            graph[i].clear();
            for (int j = 0; j < totalNodes; ++j) {
                capacity[i][j] = 0;
                flowPassed[i][j] = 0;
            }
        }

        map<string, int> sizeToNode;
        int nodeCounter = 1;

        sizeToNode["XXL"] = nodeCounter++;
        sizeToNode["XL"] = nodeCounter++;
        sizeToNode["L"] = nodeCounter++;
        sizeToNode["M"] = nodeCounter++;
        sizeToNode["S"] = nodeCounter++;
        sizeToNode["XS"] = nodeCounter++;

        for (int i = 1; i <= 6; ++i) {
            capacity[source][i] = N / 6; 
            graph[source].push_back(i);
            graph[i].push_back(source);
        }

        for (int i = 0; i < M; ++i) {
            string size1, size2;
            cin >> size1 >> size2;

            int id1 = sizeToNode[size1];
            int id2 = sizeToNode[size2];
            int personNode = 6 + i + 1; 

            capacity[id1][personNode] = 1;
            graph[id1].push_back(personNode);
            graph[personNode].push_back(id1);

            capacity[id2][personNode] = 1;
            graph[id2].push_back(personNode);
            graph[personNode].push_back(id2);
        }

        for (int i = 1; i <= M; ++i) {
            int personNode = 6 + i;
            capacity[personNode][sink] = 1;
            graph[personNode].push_back(sink);
            graph[sink].push_back(personNode);
        }

        int maxFlow = edmonds_karp(source, sink, totalNodes);

        if (maxFlow == M) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
