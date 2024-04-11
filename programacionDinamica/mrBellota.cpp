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

int calcularMejorRecorrido(int altura, int arbolActual){
    if(altura < 0){
        return 0;
    }
    if(DP[arbolActual][altura] !=-1 ){
        return DP[arbolActual][altura];
    }
    int parcial = 0;
    for(int i=0; i<cantidadArboles;i++){
        if(altura == alturaHistorica-1){
            parcial =  bellotas[i][altura] + calcularMejorRecorrido(altura-1,i);
            if(DP[arbolActual][altura]< parcial){
                DP[arbolActual][altura] = parcial;
            }
        }
        else if (i ==arbolActual){
            parcial =  bellotas[arbolActual][altura] + calcularMejorRecorrido(altura-1,i);
            if(DP[arbolActual][altura]< parcial){
                DP[arbolActual][altura] = parcial;
            }
        }
        else {
            parcial =  bellotas[arbolActual][altura] + calcularMejorRecorrido(altura-caidaPorSalto,i);
            if(DP[arbolActual][altura]< parcial){
                DP[arbolActual][altura] = parcial;
            }
        }
    }
    if(DP[arbolActual][altura]>maximo){
        maximo = DP[arbolActual][altura];
    }
    return DP[arbolActual][altura];
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