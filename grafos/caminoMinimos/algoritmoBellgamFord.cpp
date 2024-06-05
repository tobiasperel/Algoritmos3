#include <iostream>
#include <vector>
#include <tuple>
#include <limits>

using namespace std;

class Graph {
    int V; // Número de vértices
    vector<tuple<int, int, int>> edges; // Lista de aristas (u, v, w)

public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    bool bellmanFord(int src);
};

Graph::Graph(int V) {
    this->V = V;
}

void Graph::addEdge(int u, int v, int w) {
    edges.push_back(make_tuple(u, v, w));
}

bool Graph::bellmanFord(int src) {
    vector<int> dist(V, numeric_limits<int>::max());
    dist[src] = 0;

    // Relajar todas las aristas V-1 veces
    for (int i = 1; i <= V - 1; ++i) {
        for (const auto& e : edges) {
            int a, b, w;
            tie(a, b, w) = e;
            if (dist[a] != numeric_limits<int>::max() && dist[a] + w < dist[b]) {
                dist[b] = dist[a] + w;
            }
        }
    }

    // Verificar si hay ciclos negativos
    for (const auto& e : edges) {
        int a, b, w;
        tie(a, b, w) = e;
        if (dist[a] != numeric_limits<int>::max() && dist[a] + w < dist[b]) {
            cout << "El grafo contiene un ciclo negativo." << endl;
            return true; // Hay un ciclo negativo
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

    return false; // No hay ciclo negativo
}

int main() {
    int V = 6; // Número de vértices
    Graph g(V);

    // Añadir aristas (u, v, w) - arista desde u a v con peso w
    g.addEdge(0, 1, 5);  // Nodo 1 a Nodo 2 con peso 5
    g.addEdge(1, 2, 5);  // Nodo 2 a Nodo 3 con peso 5
    g.addEdge(2, 3, 5);  // Nodo 3 a Nodo 4 con peso 5
    g.addEdge(0, 4, 6);  // Nodo 1 a Nodo 5 con peso 6
    g.addEdge(4, 5, 5);  // Nodo 5 a Nodo 6 con peso 5
    g.addEdge(3, 1, -4); // Arista negativa para probar el ciclo negativo

    if (!g.bellmanFord(0)) { // Ejecutar Bellman-Ford desde el nodo 0
        cout << "No se detectaron ciclos negativos en el grafo." << endl;
    }

    return 0;
}
