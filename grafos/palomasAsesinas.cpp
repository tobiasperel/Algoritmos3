#include<iostream>
#include<vector>
#include<queue>
using namespace std;

const int MAXN = 1000;
vector<vector<int>> aristas;

int main(){
    int n, m, u, v;
    cin >> n >> m;
    cin >> u >> v;
    aristas.resize(1000);
    while(u != 0 && v != 0){
        aristas[u].push_back(v);
        aristas[v].push_back(u);
        cin >> u >> v;
    }
    return 0;
}