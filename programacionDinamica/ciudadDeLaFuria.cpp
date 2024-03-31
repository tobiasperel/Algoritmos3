#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct edificio{
    int altura;
    int ancho;
};

int main(){
    int casos;
    cin >> casos;
    
    string superFrase = "";
    
    for(int caso = 0; caso < casos; caso++){
        int numeroDeEdificios;
        cin >> numeroDeEdificios;
        
        vector<edificio> edificios(numeroDeEdificios);
        vector<int> crecimiento(numeroDeEdificios);
        vector<int> decrecimiento(numeroDeEdificios);
        
        for(int i = 0; i < numeroDeEdificios; i++){
            cin >> edificios[i].altura;
        }
        
        for(int i = 0; i < numeroDeEdificios; i++){
            cin >> edificios[i].ancho;
        }
        
        for(int i = 0; i < numeroDeEdificios; i++){
            crecimiento[i] = decrecimiento[i] = edificios[i].ancho;
        }
        
        for(int i = 1; i < numeroDeEdificios; i++){
            for(int j = 0; j < i; j++){
                if(edificios[i].altura > edificios[j].altura){
                    crecimiento[i] = max(crecimiento[i], crecimiento[j] + edificios[i].ancho);
                }
                else if(edificios[i].altura < edificios[j].altura){
                    decrecimiento[i] = max(decrecimiento[i], decrecimiento[j] + edificios[i].ancho);
                }
            }
        }
        
        int maxCrecimiento = *max_element(crecimiento.begin(), crecimiento.end());
        int maxDecrecimiento = *max_element(decrecimiento.begin(), decrecimiento.end());
        
        if(maxCrecimiento >= maxDecrecimiento)
            superFrase += "Case " + to_string(caso + 1) + ". Increasing (" + to_string(maxCrecimiento) + "). Decreasing (" + to_string(maxDecrecimiento) + ").\n";
        else
            superFrase += "Case " + to_string(caso + 1) + ". Decreasing (" + to_string(maxDecrecimiento) + "). Increasing (" + to_string(maxCrecimiento) + ").\n";
    }
    
    cout << superFrase;
    
    return 0;
}
