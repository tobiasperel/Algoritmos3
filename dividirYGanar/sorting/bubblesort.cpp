#include<iostream>
#include<vector>
using namespace std;

// complejidad de tiempo O(n^2)


void bubbleSort(vector<int>&array){
    for(int i=0; i<array.size();i++){
        for(int j=0; j<array.size()-1;j++){
            if(array[j]>array[j+1]){
                swap(array[j],array[j+1]);
            }
        }
    }
}

int main(){
    vector<int>array = {9,3,2,5,4};
    bubbleSort(array);
    for(int i=0;i<array.size();i++){
        cout<<array[i]<<" ";
    }
}