#include<iostream>
#include<vector>
using namespace std;


int vinoGoloso(vector<int> borrachos){
    int costo = 0;
    int parcial = 0;
    for(int i=0;i<borrachos.size();i++){
        borrachos[i] += parcial;
        parcial = borrachos[i];
        borrachos[i] = 0;
        costo += abs(parcial);
    }
    return costo;
}

int main(){
    int habitantes;
    cin >> habitantes;
    string superFrase = "";
    while (habitantes != 0) {
        vector<int> borrachos(habitantes);
        for(int j=0; j<habitantes; j++){
            cin >> borrachos[j];
        }
        vinoGoloso(borrachos);
        superFrase+= to_string(vinoGoloso(borrachos)) + "\n";
        cin >> habitantes;
    }
    cout<<superFrase;
    return 0;
}