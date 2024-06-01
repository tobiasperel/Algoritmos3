#include<iostream>
#include<vector>
#include<tuple>

using namespace std;
vector<vector<int>> grafo;
vector<tuple<int, int>> lucesCambiadas;
vector<bool> visitado;
vector<bool> lucesPrendidas;
string superMensaje = "";

void dfs(int u) {
    visitado[u] = true;
    cout<<u<<endl;
    for (int v : grafo[u]) {
        if (!visitado[v]) {
            dfs(v);
        }
    }
} 

void llegarALaCama(int u, int ultimaHabitacion ) {
    visitado[u] = true;
    for (int v : grafo[u]) {
        if ((lucesCambiadas[u] == make_tuple(u, v) || lucesCambiadas[u] == make_tuple(v, u) ) ) {
            lucesPrendidas[v] = true;
            superMensaje += "- Switch on light in room" + to_string(v) + ".\n";
            
            llegarALaCama(v, u);
        }
        if(lucesPrendidas[v]){
            llegarALaCama(v,u);
        }
    }
}

int main() {
    int r, d, s,casos=0;
    while (true) {
        cin >> r >> d >> s;
        if (r == 0 && d == 0 && s == 0) break;  

        grafo.resize(r+1);  // Ajusta el tamaño del grafo al número de habitaciones + 1
        lucesCambiadas.resize(s);  // Ajusta el tamaño de lucesCambiadas al número de interruptores
        visitado.resize(r+1,false);  // Ajusta el tamaño de visitado al número de habitaciones + 1
        lucesPrendidas.resize(r+1,false);  // Ajusta el tamaño de lucesPrendidas al número de habitaciones + 1
        int i, j;
        for (int k = 0; k < d; k++) {
            cin >> i >> j;
            grafo[j].push_back(i);
            grafo[i].push_back(j);
        }

        for (int k = 0; k < s; k++) {
            cin >> i >> j;
            lucesCambiadas[k] = make_tuple(i, j);  // Almacena la información del interruptor
        }

        dfs(1);
        if(!visitado[r]) superMensaje += "Villa #" + to_string(casos++) + "\nThe problem cannot be solved.\n";    
        else{
            visitado.clear();
            visitado.resize(r+1,false);
            llegarALaCama(1,0);
        }   
        visitado.clear();
        grafo.clear();  
        lucesCambiadas.clear();  
    }
    cout<<superMensaje;

    return 0;
}