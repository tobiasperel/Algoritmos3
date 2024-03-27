#include<iostream>
#include<vector>
using namespace std;

void findCombinations(vector<int>numeros,vector<int>&temporal,int index, int suma,int objetivo){

    if(suma == objetivo){
        cout << "Combinacion encontrada: ";
        for (int j= 0; j < temporal.size(); j++){
            cout << temporal[j] << " ";
        }
        cout << endl;
        return;
    }

    for (int i=index;i<numeros.size();i++){
        if(i!= index && numeros[i]  ==  numeros[i-1]) continue; // cuando i= index significa que estas al comienzo de una rama y que no necesariamente el elemento que tenes antes lo analisaste.
        if(suma + numeros[i]<= objetivo){
            temporal.push_back(numeros[i]);
            findCombinations(numeros,temporal,i+1,suma + numeros[i],objetivo);
            temporal.pop_back() ; //saca el ultimo elemento. Hay dos opciones o llega a la objetivo o recorre todo el for, nunca llega entar al if y va para atras.
        }
        
    }
    
}


int main (){
    int cantidad;
    cin >> cantidad;
    vector<int> numeros;
    vector<int> temporal;
    for (int i = 0; i < cantidad; i++){
        int n;
        cin >> n;
        numeros.push_back(n);
    }
    int objetivo;
    cin >> objetivo;
    findCombinations(numeros,temporal,0,0,objetivo);
    return 0;
}