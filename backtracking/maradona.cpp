#include<iostream>
#include<vector>
using namespace std;


void encontrarMejorFormacion(vector<string>&nombres,vector<int>ataque,vector<int>defensa, vector<string>&formacion,int sumaAtacantes, int sumaDefensas,int recordAtaque, int recordDefensa, int index){
    if(index == 4 && sumaAtacantes>=recordAtaque){
        if(sumaAtacantes==recordAtaque){
            int defensaParical = 0;
            for(int i=5;i<10;i++){
                defensaParical+=defensa[i];
            }
            if(defensaParical>recordDefensa){
                nombres = formacion;
            } // falta agregar esto, "If there is still more than one combination, pick the attackers that come lexicographically earliest."
            return;
        }
        nombres = formacion;
        return;
    }
    for(int i=index;i<10;i++){
        if(sumaAtacantes>)
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
    for(int i=0;i<10;i++){
        cin>> nombre;
        nombres.push_back(nombre);
        cin>>score;
        ataque.push_back(score);
        cin>>score;
        defensa.push_back(score);
    }

    return 0;
}