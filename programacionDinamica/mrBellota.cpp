#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<vector<int>> bellotas;
vector<vector<int>> DP;
int maximo = -1;
int alturaHistorica;
int caidaPorSalto;
int cantidadArboles;
vector<int>maximoPorFila;

int calcularMejorRecorrido(int altura, int arbolActual){
    for(int i= 0; i< alturaHistorica; i++){
        for(int j = 0; j < cantidadArboles; j++){
            if(DP[j][i] == -1){
                if(i == 0){
                    DP[j][i] = bellotas[j][i] ;
                }
                else if(i- caidaPorSalto < 0){
                    DP[j][i] = bellotas[j][i] + DP[j][i-1];
                }else{
                    DP[j][i] = bellotas[j][i] + max(DP[j][i-1],maximoPorFila[i-caidaPorSalto]);
                }
            }
            if(DP[j][i] > maximo){
                maximo = DP[j][i];
            }
            if(DP[j][i] > maximoPorFila[i]){
                maximoPorFila[i] = DP[j][i];
            }
        }
    }
}    

int main(){
    vector<int> respuestas;
    int casos;
    cin >> casos;

    int alturaArboles;

    for(int caso = 0; caso < casos; caso++){
        cin>>cantidadArboles;
        
        cin>>alturaArboles;
        
        cin>> caidaPorSalto;
        
        for(int i = 0; i < cantidadArboles; i++){
            int cantidadDeBellotas;
            cin>>cantidadDeBellotas;
            bellotas.push_back(vector<int>());
            DP.push_back(vector<int>());
            for(int k = 0;k <alturaArboles;k++){
                DP[i].push_back(-1);
                bellotas[i].push_back(0);
                maximoPorFila.push_back(0);
            }
            for(int j = 0; j < cantidadDeBellotas; j++){
                int alturaBellota;
                cin>>alturaBellota;
                bellotas[i][alturaBellota-1] += 1;
            }
        }
        alturaHistorica = alturaArboles;
        if(caso == casos-1){
            cin>> maximo;
        }
        maximo = 0;
        calcularMejorRecorrido(alturaArboles-1,0);
        respuestas.push_back(maximo);
        bellotas.clear();
        DP.clear();
    }
    for(int i = 0; i < respuestas.size(); i++){
        cout<<respuestas[i]<<endl;
    }
    return 0;
}