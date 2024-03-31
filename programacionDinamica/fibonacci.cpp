#include<iostream>
#include<vector>
using namespace std;

vector<int>numeros;

int sucesionFibonacciBack(int n){
    if(n == 0 || n == 1){
        return 1;
    }
    return sucesionFibonacciBack(n-1) + sucesionFibonacciBack(n-2);
}

int sucesionFibonacciDP(int n){
    if(n == 0 || n == 1){
        return 1;
    }

    if(numeros[n-1]==-1){
        numeros[n-1] = sucesionFibonacciDP(n-1) + sucesionFibonacciDP(n-2);
    }
    return numeros[n-1];
}

int main(){
    int numeroSecuencia = 35;
    cout<<sucesionFibonacciBack(numeroSecuencia)<<endl;

    for(int i = 0; i<numeroSecuencia;i++){
        numeros.push_back(-1);
    }
    cout<<sucesionFibonacciDP(numeroSecuencia);
    return 0;
}