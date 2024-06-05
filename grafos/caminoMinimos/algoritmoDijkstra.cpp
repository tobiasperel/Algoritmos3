#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

typedef pair<int, int> Edge; // Define una arista como un par de enteros (destino, peso)

class Graph {
    int V; // Número de vértices
    vector<vector<Edge>> adj; // Lista de adyacencia

public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    void dijkstra(int src);
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int u, int v, int w) {
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w); // Si el grafo es dirigido, eliminar esta línea
}

void Graph::dijkstra(int src) {
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq; // Min-heap
    vector<int> dist(V, numeric_limits<int>::max()); // Distancias inicializadas a infinito

    pq.emplace(0, src);
    dist[src] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            // Si se encuentra una distancia menor
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.emplace(dist[v], v);
            }
        }
    }

    // Imprimir las distancias más cortas desde src
    cout << "Distancias desde el nodo " << src << ":\n";
    for (int i = 0; i < V; ++i) {
        if (dist[i] == numeric_limits<int>::max()) {
            cout << "Nodo " << i << " está inaccesible.\n";
        } else {
            cout << "Distancia al nodo " << i << " es " << dist[i] << ".\n";
        }
    }
}

int main() {
    int V = 7; // Número de vértices
    Graph g(V);

    // Añadir aristas (u, v, w) - arista desde u a v con peso w
    g.addEdge(0, 1, 5); // Nodo 1 a Nodo 2 con peso 5
    g.addEdge(1, 2, 5); // Nodo 2 a Nodo 3 con peso 5
    g.addEdge(2, 3, 5); // Nodo 3 a Nodo 4 con peso 5
    g.addEdge(0, 4, 6); // Nodo 1 a Nodo 5 con peso 6
    g.addEdge(4, 5, 6); // Nodo 5 a Nodo 6 con peso 5
    g.addEdge(5,6,1); // Nodo 5 a Nodo 6 con peso 1
    g.addEdge(6,3,1); // Nodo 5 a Nodo 6 con peso 1
    g.dijkstra(0); // Ejecutar Dijkstra desde el nodo 0

    return 0;
}
