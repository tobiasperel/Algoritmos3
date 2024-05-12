#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<vector<int>> aristas;
vector<bool> visitado;

void dfs(int v){
    visitado[v] = true;
    cout << "Visitando nodo " << v << endl;
    for(int u : aristas[v]){
        if(!visitado[u]){
            dfs(u);
        }
    }
}

int main(){
    int n, m;
    cin >> n >> m;
    aristas.resize(n);
    visitado.resize(n, false);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        aristas[u].push_back(v);
        aristas[v].push_back(u);
    }
    dfs(0);
    for(int i = 0; i < n; i++){
        if(!visitado[i]){
            cout << "No se visito el nodo " << i << endl;
        }
    }
    return 0;
}