#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<vector<int>> aristas;
vector<bool> visitado;
vector<int> distancias;

void bfs(int v){
    stack<int> pila;
    pila.push(v);
    visitado[v] = true;
    distancias[v] = 0;
    while(!pila.empty()){
        int u = pila.top();
        pila.pop();
        cout << "Visitando nodo " << u << endl;
        for(int w : aristas[u]){
            if(!visitado[w]){
                visitado[w] = true;
                distancias[w] = distancias[u] + 1;
                pila.push(w);
            }
        }
    }
    
}

int main(){
    int n, m;
    cin >> n >> m;
    aristas.resize(n);
    visitado.resize(n, false);
    distancias.resize(n);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        aristas[u].push_back(v);
        aristas[v].push_back(u);
    }
    
    bfs(0);
    for(int i = 0; i < n; i++){
        cout << "Distancia al nodo " << i << ": " << distancias[i] << endl;
    }
    return 0;
}