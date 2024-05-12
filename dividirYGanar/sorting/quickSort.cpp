#include<iostream>
#include<vector>

using namespace std;

void quickSort(vector<int> &v, int l, int r){
    if(l >= r) return;
    int i = l, j = r, pivote = v[(l + r) / 2];
    while(i <= j){
        while(v[i] < pivote) i++;
        while(v[j] > pivote) j--;
        if(i <= j){
            swap(v[i], v[j]);
            i++;
            j--;
        }
    }
    quickSort(v, l, j);
    quickSort(v, i, r);
}


int main(){
    int n = 10;
    vector<int> v = {5, 3, 2, 1, 40, 6, 7, 8, 8, 10};
    quickSort(v, 0, n - 1);
    for(int i = 0; i < n; i++){
        cout << v[i] << " ";
    }
    cout << endl;
    return 0;
}