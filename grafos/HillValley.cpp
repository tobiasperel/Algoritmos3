#include<iostream>
#include<vector>

using namespace std;
vector<vector<int>> grafo;
vector<tuple<int, int, int>> lucesCambiadas;
int main(){ //r es numero de habitaciones, d es numero de puertas, s es numero de interruptores
    int r,d,s;
    cin >> r >> d >> s;
    grafo.resize(d);
    for (int k = 0; k< d; k++){
        int i,j;
        grafo[i].push_back(j);
    }
    for (int i = 0; i< s; i++){
        int k,l;
        lucesCambiadas.push_back({k,l});
    }
    cin>>r>>d>>s;
    return 0;
}