#include<iostream>
#include<vector>
using namespace std;

struct edifio{
    int height;
    int width;
};

int record =0;


void calcularCremiento(vector<edifio>&data,int numeroDeEdificios, int index, int sumaParcial,vector<edifio>parcial,int alturaAnterior){
    
    if(index == numeroDeEdificios&sumaParcial>record){
            record = sumaParcial;
            return;
    }
    for(int i= index;i<numeroDeEdificios;i++){
        if(data[i].height>=alturaAnterior){
            parcial.push_back(data[i]);
            calcularCremiento(data,numeroDeEdificios,i+1,sumaParcial+data[i].width,parcial,data[i].height);
            parcial.pop_back(); 
        }else{
            continue;
        }
        
        
    } 
    
}

int main(){
    int casos;
    string superFrase= "";
    cin>> casos;
    int numeroDeEdificios;
    cin>> numeroDeEdificios;
    vector<edifio>data;
    vector<edifio>parcial;
    int medida;
    for(int i=0; i<numeroDeEdificios;i++){
        cin>>medida;
        edifio temp;
        temp.height = medida;
        data.push_back(temp);
    }
    for(int i=0; i<numeroDeEdificios;i++){
        cin>>medida;
        data[i].width = medida;
    }
    calcularCremiento(data,numeroDeEdificios,0,0,parcial,0);
    cout<<record;
    return 0;
}