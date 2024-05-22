#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//Complejidad O(n + k) donde k es el rango de los elementos

void countingSort(vector<int> &v){
    int n = v.size();
    int maximo = *max_element(v.begin(), v.end());
    int minimo = *min_element(v.begin(), v.end());
    int rango = maximo - minimo + 1;
    vector<int> count(rango), output(n);
    for(int i = 0; i < n; i++){
        count[v[i] - minimo]++;
    }
    for(int i = 1; i < rango; i++){
        count[i] += count[i - 1];
    }
    for(int i = n - 1; i >= 0; i--){
        output[count[v[i] - minimo] - 1] = v[i];
        count[v[i] - minimo]--;
    }
    for(int i = 0; i < n; i++){
        v[i] = output[i];
    }
}

int main(){
    int n = 10;
    vector<int> v = {5, 3, 2, 1, 40, 6, 7, 8, 8, 10};
    countingSort(v);
    for(int i = 0; i < n; i++){
        cout << v[i] << " ";
    }
    cout << endl;
    return 0;
}