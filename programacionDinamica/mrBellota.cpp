#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<vector<int>> bellotas;
vector<vector<int>> DP;
int maximo = -1;


int calcularMejorRecorrido(int altura, int cantArboles, int caidaPorSalto, int ultimoArbol){
    if(altura < 0){
        return 0;
    }
    for(int i = altura; i >= 0; i--){
        for(int j = 0; j < cantArboles; j++){
            if(DP[j][i] == -1){
                DP[j][i] = bellotas[j][i] + max(calcularMejorRecorrido(i-1, cantArboles, caidaPorSalto, j), calcularMejorRecorrido(i-caidaPorSalto, cantArboles, caidaPorSalto, j));
                if(DP[j][i] > maximo){
                    maximo = DP[j][i];
                }
            }
        }    
    }
    return 0;
}

int main(){

    int casos;
    cin >> casos;

    int cantidadArboles;
    int alturaArboles;
    int caidaPorSalto;

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
        calcularMejorRecorrido(alturaArboles-1,cantidadArboles,caidaPorSalto,-1);
        // for(int i=0; i<cantidadArboles;i++){
        //    for(int j=0; j<alturaArboles;j++){
        //        cout<<DP[i][j]<<" ";
        //    }
        // }
        cout<<maximo<<endl;
    }

    return 0;
}