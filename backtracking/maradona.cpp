#include<iostream>
#include<vector>
using namespace std;


void encontrarMejorFormacion(vector<string>nombres,vector<int>ataque,vector<int>defensa, vector<string>&parcial,vector<string> ganadorProvisorio,int sumaAtacantes,int recordAtaque, int index){
    if(parcial.size() == 5 ){
        if (sumaAtacantes > recordAtaque || sumaAtacantes == recordAtaque){
            recordAtaque = sumaAtacantes;
            ganadorProvisorio = parcial;
            
        }
        return;
    }
    for(int i = index;i<10;i++){
        parcial.push_back(nombres[i]);
        encontrarMejorFormacion(nombres,ataque,defensa,parcial,ganadorProvisorio,sumaAtacantes+ataque[i],recordAtaque,index +1);
        parcial.pop_back();
    }
    
    

}

int main(){
    int casos;
    cin >> casos;
    vector<string>nombres;
    vector<int> ataque;
    vector<int> defensa;
    string nombre;
    int score;
    vector<string> parcial; // Add this line
    vector<string> ganadorProvisorio;

    for(int i=0;i<10;i++){
        cin>> nombre;
        nombres.push_back(nombre);
        cin>>score;
        ataque.push_back(score);
        cin>>score;
        defensa.push_back(score);
    }
    int sumaTotal = 0;
    for(int i =0; i<10;i++){
        sumaTotal+= ataque[i];
    }
    encontrarMejorFormacion(nombres,ataque,defensa,parcial,ganadorProvisorio,0,0,0);
    return 0;
}