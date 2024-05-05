#include<iostream>
#include<vector>
using namespace std;


long vinoGoloso(vector<int> borrachos){
    long costo = 0;
    long parcial = 0;
    for(int i=0;i<borrachos.size();i++){
        borrachos[i] += parcial;
        parcial = borrachos[i];
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
        superFrase+= to_string(vinoGoloso(borrachos)) + "\n";
        cin >> habitantes;
    }
    cout<<superFrase;
    return 0;
}