#include<iostream>
#include<vector>
using namespace std;

int longitud;
vector<int>pasos;

int cambiarLetras(string p1,string p2){
    int cantidadDeOperaciones =0;
    int cantA =0;
    int cantB =0;
    for(int i=0;i<longitud;i++){
        if(p1[i] == p2[i]){ // pensar como que lo que esta atas esta limpio
            if(p1[i] == 'a'){
                cantA +=2;
            }
            else{
                cantB +=2;
            }
            continue;
        }
        if (p1[i] !=p2[i+1]){
            char aux = p1[i];
            p1[i] = p2[i+1];
            p2[i+1] = aux;
        } 
    }
    if(cantA1 != cantA2 || cantB1 != cantB2){
        return -1;
    }
    return cantidadDeOperaciones;
}

int main(){
    
    cin>> longitud;
    string p1,p2;
    cin>>p1;
    cin>>p2;
    
    return 0;
}