#include<iostream>
#include<vector>
using namespace std;

// complejidad de tiempo O(n^2) mas efeciente que bubbleSort
// omeg(n) y O(n^2) en el peor caso

void insertionSort(vector<int>&array){
    for(int i=1; i<array.size();i++){
        int j = i;
        while (array[j-1]>array[j]){
            swap (array[j-1],array[j]);
            j--;
            if (j==0) break;
        } 
        }
}


int main(){
    vector<int>array = {9,3,2,5,4};
    insertionSort(array);
    for(int i=0;i<array.size();i++){
        cout<<array[i]<<" ";
    }
}