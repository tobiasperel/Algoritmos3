#include<iostream>
#include<vector>
using namespace std;

//armar el heap es de O(n). Luego cada vez que se saca un elemento volver a armar el heap es de O(log n). Fijarse que lo que se hace es hacer log n permutaciones como maximo. Esto lo repito n veces, por lo que el costo total es O(n log n)

// 1.armar el heap O(n)
// 2. heapify O(log n) esto lo repito n veces
// Complejidad O(n log n) + O(n) = O(n log n) 

void heapify(vector<int> &v, int n, int i){
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if(l < n && v[l] > v[largest]) largest = l;
    if(r < n && v[r] > v[largest]) largest = r;
    if(largest != i){
        swap(v[i], v[largest]);
        heapify(v, n, largest);
    }
}

void heapSort(vector<int> &v){
    int n = v.size();
    for(int i = n / 2 - 1; i >= 0; i--){
        heapify(v, n, i);
    }
    for(int i = n - 1; i >= 0; i--){
        swap(v[0], v[i]);
        heapify(v, i, 0);
    }
}

int main(){
    int n = 10;
    vector<int> v = {5, 3, 2, 1, 40, 6, 7, 8, 8, 10};
    heapSort(v);
    for(int i = 0; i < n; i++){
        cout << v[i] << " ";
    }
    cout << endl;
    return 0;
}