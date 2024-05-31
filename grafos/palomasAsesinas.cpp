#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

const int MAXN = 1000;
vector<vector<int>> aristas;
vector<bool> visitado;
vector<int> hijos;
vector<int> tin;
vector<int> low;
int tiempo;

void dfs(int v, int p){
    visitado[v] = true; 
    tin[v] = low[v] = tiempo++;
    int hijo = 0;
    for(int i = 0; i < aristas[v].size(); i++){
        if(aristas[v][i] == p){
            continue;
        }
        if(visitado[aristas[v][i]]){
            low[v] = min(low[v], tin[aristas[v][i]]);
        } else {
            dfs(aristas[v][i], v);
            low[v] = min(low[v], low[aristas[v][i]]);
            if(low[aristas[v][i]] >= tin[v] && p != -1){
                hijo++;
            }
        }
    }
    hijos[v] = hijo;
}

int main(){
    int n, m, u, v;
    cin >> n >> m;
    string superFrase = "";
    while(n != 0 && m != 0){
        aristas.assign(n, vector<int>()); // Resetear las aristas para cada nuevo caso
        cin >> u >> v;
        while(u != -1 && v != -1){
            aristas[u].push_back(v);
            aristas[v].push_back(u);
            cin >> u >> v;
        }
        tiempo = 0;
        tin.assign(n, -1);
        low.assign(n, -1);
        visitado.assign(n, false);
        hijos.assign(n, 0);
        for(int i = 0; i < n; i++){
            if(!visitado[i]){
                dfs(i, -1);
            }
        }

        vector<int> indices(n);
        for(int i = 0; i < n; i++){
            indices[i] = i;
        }

        sort(indices.begin(), indices.end(), [](int a, int b){
            if(hijos[a] + 1 == hijos[b] + 1) {
                return a < b;
            }
            return hijos[a] + 1 > hijos[b] + 1;
        });

        
        for(int i = 0; i < m && i < indices.size(); i++){
            superFrase += to_string(indices[i]) + " " + to_string(hijos[indices[i]] + 1) + "\n";
        }

        cin >> n >> m;
    }
    cout<<superFrase;
    return 0;
}