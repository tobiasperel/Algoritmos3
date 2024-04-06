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

int sucesionFibonacciDPTopDown(int n){
    if(n == 0 || n == 1){
        return 1;
    }

    if(numeros[n-1]==-1){
        numeros[n-1] = sucesionFibonacciDPTopDown(n-1) + sucesionFibonacciDPTopDown(n-2);
    }
    return numeros[n-1];
}

int sucesionFibonacciDPBottomUp(int n,int index) {
    
    if(index == n){
        return numeros[n];
    }
    numeros[index+2] = numeros[index] + numeros[index+1];
    return sucesionFibonacciDPBottomUp(n,index+1);

}

int main(){
    int numeroSecuencia = 9;
    // cout<<sucesionFibonacciBack(numeroSecuencia)<<endl;

    for(int i = 0; i<numeroSecuencia-1;i++){
        numeros.push_back(-1);
    }
    cout<<sucesionFibonacciDPTopDown(numeroSecuencia-1);
    cout<<endl;
    for(int i = 0; i<numeroSecuencia-1;i++){
        numeros[i] = -1;
    }
    numeros[0] = 1;
    numeros[1] = 1;
    cout<<sucesionFibonacciDPBottomUp(numeroSecuencia-1,0);
    return 0;
}