#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

// Definir el número de vértices del grafo
#define V 4

// Una función de utilidad para imprimir la matriz de solución
void printSolution(const vector<vector<int>> &dist)
{
    cout << "La siguiente matriz muestra las distancias más cortas entre cada par de vértices:" << endl;
    for (int i = 0; i < V; ++i)
    {
        for (int j = 0; j < V; ++j)
        {
            if (dist[i][j] == INT_MAX)
                cout << "INF" << "     ";
            else
                cout << dist[i][j] << "     ";
        }
        cout << endl;
    }
}

// Implementación del algoritmo de Floyd-Warshall
void floydWarshall(vector<vector<int>>& graph) {
    vector<vector<int>> dist = graph; // Crear una matriz de distancias, inicializada con el grafo original

    // Agregar todos los vértices uno por uno al conjunto de vértices intermedios.
    for (int k = 0; k < 1; ++k) {
        bool updated = false; // Bandera para verificar si hubo actualizaciones

        // Elegir todos los vértices como fuente uno por uno
        for (int i = 0; i < V; ++i) {
            // Elegir todos los vértices como destino para la fuente elegida
            for (int j = 0; j < V; ++j) {
                // Si el vértice k está en el camino más corto de i a j, entonces actualizar el valor de dist[i][j]
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                    cout << i<<j<<k<<endl;
                    dist[i][j] = dist[i][k] + dist[k][j];
                    updated = true; // Indicar que hubo una actualización
                }
            }
        }

        // Si no hubo actualizaciones, se puede terminar antes de tiempo
        if (!updated) {
            break;
        }
    }

    // Imprimir la matriz de distancias
    printSolution(dist);
}

int main()
{
    /* Let us create the following weighted graph
           10
      (0)------->(3)
       |         /|\
     5 |          |
       |          | 1
      \|/         |
      (1)------->(2)
           3           */
    vector<vector<int>> graph = {{0, 1, 2, 3},
                                 {2, 0, 1, 4},
                                 {3, 1, 0, 5},
                                 {1, 3, 1, 0}};

    // Ejecutar el algoritmo de Floyd-Warshall
    floydWarshall(graph);

    return 0;
}
