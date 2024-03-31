#include<iostream>
#include<vector>
#include <climits>

using namespace std;

struct edifio{
    int height;
    int width;
};

int recordCrecimiento =0;
int recordDecrecimiento =0;

vector<int>dp;


int calcularCremiento(vector<edifio>&data,int numeroDeEdificios, int index, int sumaParcial,vector<edifio>parcial,int alturaAnterior){
    if(index == numeroDeEdificios){
        if(sumaParcial>recordCrecimiento){
            recordCrecimiento = sumaParcial;
        }
        return 0;
    }
    
    for(int i = index;i<numeroDeEdificios;i++){
        if(data[i].height>alturaAnterior){
            if(dp[index]!=-1){
                return dp[index];
            }   
            parcial.push_back(data[i]);
            dp[i] = data[i].height+calcularCremiento(data,numeroDeEdificios,i+1,sumaParcial+data[i].width,parcial,data[i].height);
            parcial.pop_back();
        }
    }
    if(sumaParcial>recordCrecimiento){
        recordCrecimiento = sumaParcial;
    }
    return sumaParcial;
}

int calcularDeCremiento(vector<edifio>&data,int numeroDeEdificios, int index, int sumaParcial,vector<edifio>parcial,int alturaAnterior){
    
    if(index == numeroDeEdificios){
        return 0;
    }
    if(dp[index]!=-1){
        return dp[index];
    }
    for(int i = index;i<numeroDeEdificios;i++){
        if(data[i].height<alturaAnterior){
            parcial.push_back(data[i]);
            dp[i] = calcularCremiento(data,numeroDeEdificios,i+1,sumaParcial+data[i].width,parcial,data[i].height);
            parcial.pop_back();
        }
    }
    return sumaParcial;
}


int main(){
    int casos;
    string superFrase= "";
    cin>> casos;
    for(int caso = 0; caso<casos;caso++){
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
        
        for(int i = 0; i<numeroDeEdificios;i++){
            dp.push_back(-1);
        }
        calcularCremiento(data,numeroDeEdificios,0,0,parcial,0);
        for(int i = 0; i<numeroDeEdificios;i++){
            dp.push_back(-1);
        }
        recordDecrecimiento =  calcularDeCremiento(data,numeroDeEdificios,0,0,parcial,INT_MAX);
        if(recordCrecimiento>=recordDecrecimiento)
            superFrase += "Case " + to_string(caso + 1) + ". Increasing (" + to_string(recordCrecimiento)+  "). Decreasing (" +to_string(recordDecrecimiento) + ").\n";
        else
            superFrase += "Case " + to_string(caso + 1) + ". Decreasing (" + to_string(recordDecrecimiento)+  "). Increasing (" +to_string(recordCrecimiento) + ").\n";
        recordCrecimiento =0;
        recordDecrecimiento =0;
    }
    cout<<superFrase;
    return 0;
}