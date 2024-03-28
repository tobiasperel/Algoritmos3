#include<iostream>
#include<vector>
using namespace std;

int sucesionFibonacciBack(int n){
    if(n == 0 || n == 1){
        return 1;
    }
    return sucesionFibonacciBack(n-1) + sucesionFibonacciBack(n-2);
}

int sucesionFibonacciDP(vector<int>numeros,int n){
    if(n == 0 || n == 1){
        return 1;
    }

    if(numeros[n-1]==-1){
        numeros[n-1] = sucesionFibonacciDP(numeros,n-1) + sucesionFibonacciDP(numeros,n-2);
    }
    return numeros[n-1];
}

int main(){
    int numeroSecuencia = 4;
    cout<<sucesionFibonacciBack(numeroSecuencia)<<endl;
    vector<int>numeros(numeroSecuencia,-1);
    cout<<sucesionFibonacciDP(numeros, numeroSecuencia);
}