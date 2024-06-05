#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

vector<vector<int>> aristas;
vector<vector<int>> pesosAristas;
int minimoDel0 = 40;
int posicionDel0;
int posiciondelChico;
void calcularCosto(vector<int> combinaciones){
    
    for(int i = 0; i < combinaciones.size(); i++){
        for(int j = 0; j < combinaciones.size(); j++){
            if(i != j && i < j){
                //calcular la diferencia digito a digito de 4 digitos
                int aux = combinaciones[i];
                int aux2 = combinaciones[j];
                
                int digito11 = aux % 10; 
                int digito21 = (aux % 100 - digito11) / 10; 
                int digito31 = (aux % 1000 - digito21 - digito11) / 100; 
                int digito41 = (aux - digito31 - digito21 -digito11)/1000;                    
                int digito12 = aux2 % 10;
                int digito22 = (aux2 % 100 - digito12) / 10; 
                int digito32 = (aux2 % 1000 - digito22 - digito12) / 100; 
                int digito42 = (aux2 - digito32 - digito22 -digito12)/1000;
                int diferencia = 0;
                diferencia += min(abs(digito11 - digito12), abs(10 - abs(digito11 - digito12)));
                diferencia +=min(abs(digito21 - digito22), abs(10 - abs(digito21 - digito22)));
                diferencia +=min(abs(digito31 - digito32), abs(10 - abs(digito31 - digito32)));
                diferencia +=min(abs(digito41 - digito42), abs(10 - abs(digito41 - digito42)));
                aristas[i].push_back(j);
                aristas[j].push_back(i);
                pesosAristas[i].push_back(diferencia);
                pesosAristas[j].push_back(diferencia);
                if(combinaciones[i] == 0){
                    if(diferencia < minimoDel0){
                        minimoDel0 = diferencia;
                        posicionDel0 = i;
                        posiciondelChico = j;
                        // cout << "posicionDel0: " << posicionDel0 << endl;
                        // cout << "posiciondelChico: " << posiciondelChico << endl;
                        // cout << "minimoDel0: " << minimoDel0 << endl;
                        // cout<<combinaciones[j]<<endl;
                    }
                }
            }
        }
    }
}

void remplazarAristas(){
    for(int i = 0; i < aristas.size(); i++){
        for(int j = 0; j < aristas[i].size(); j++){
            if(i == posicionDel0 && j+1!= posiciondelChico){
                // cout << "i: " << i << " j: " << j << endl;
                // cout<< pesosAristas[i][j] << endl;
                pesosAristas[i][j] = 40;
            }
        }
    }
}

int prim(int n) {
    vector<int> minCost(n, 40);
    vector<bool> inMST(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    minCost[0] = 0;
    pq.push({0, 0}); // (cost, node)
    
    int totalCost = 0;
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        if (inMST[u]) continue;
        
        inMST[u] = true;
        totalCost += minCost[u];
        
        for (int i = 0; i < aristas[u].size(); i++) {
            int v = aristas[u][i];
            int weight = pesosAristas[u][i];
            if (!inMST[v] && weight < minCost[v]) {
                minCost[v] = weight;
                pq.push({minCost[v], v});
            }
        }
    }
    
    return totalCost;
}

int main(){
    int casos,n;
    vector<int>combinaciones;
    cin >> casos;
    string superFrase = "";
    for(int i = 0; i < casos; i++){
        cin >> n;
        combinaciones.push_back(0);
        for(int j = 0; j < n; j++){
            int aux;
            cin >> aux;
            combinaciones.push_back(aux);
        }
        
        aristas.assign(n+1, vector<int>());
        pesosAristas.assign(n+1, vector<int>());
        calcularCosto(combinaciones);
        remplazarAristas();
        superFrase += to_string(prim(n+1)) + "\n";
        combinaciones.clear();
        minimoDel0 = 40;
    }
    cout << superFrase;
}