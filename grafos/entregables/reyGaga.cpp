// Algoritmo bellmanford basado de geeksforgeeks  https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/#bellmanford-algorithm
#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int src, dest, weight;
};


struct Graph
{
    int V, E; 
    struct Edge *edge; 
};

struct Graph *createGraph(int V, int E)
{
    struct Graph *graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edge = new Edge[E];
    return graph;
}

bool BellmanFord(struct Graph *graph, int src)
{
    int V = graph->V;
    int E = graph->E;
    int dist[V];

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    for (int i = 1; i <= V - 1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }

    for (int i = 0; i < E; i++)
    {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
        {
            return true;
        }
    }

    return false;
}

int main()
{
    int N;
    cin >> N;

    while (N > 0)
    {
        int M;
        cin >> M;

        vector<Edge> aristas;
        int s, n, k;
        string o;

        for (int i = 0; i < M; ++i)
        {
            cin >> s >> n >> o >> k;
            if (o == "lt")
            {
                aristas.push_back({s - 1, s + n, k - 1});
            }
            else
            {
                aristas.push_back({s + n, s - 1, -k - 1});
            }
        }

        for (int i = 0; i <= N; ++i)
        {
            aristas.push_back({N + 1, i, 0});
        }

        struct Graph *graph = createGraph(N + 2, aristas.size());
        for (int i = 0; i < aristas.size(); ++i)
        {
            graph->edge[i] = aristas[i];
        }

        if (BellmanFord(graph, N + 1))
        {
            cout << "successful conspiracy" << endl;
            
        }
        else
        {
            cout << "lamentable kingdom" << endl;
        }

        delete[] graph->edge;
        delete graph;

        cin >> N;
    }

    return 0;
}
