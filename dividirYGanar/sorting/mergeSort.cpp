#include <iostream>
#include <vector>

using namespace std;

// Función para combinar dos subarreglos ordenados en uno solo
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Crear arreglos temporales
    vector<int> L(n1), R(n2);

    // Copiar datos a los arreglos temporales L[] y R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Combinar los arreglos temporales de nuevo en arr[l..r]
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes de L[], si hay alguno
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de R[], si hay alguno
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Función principal que ordena arr[l..r] usando el algoritmo Merge Sort
void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        // Encuentra el punto medio del arreglo
        int m = l + (r - l) / 2;
        // Ordena la primera mitad
        mergeSort(arr, l, m);
        // Ordena la segunda mitad
        mergeSort(arr, m + 1, r);

        // Combina las mitades ordenadas
        merge(arr, l, m, r);
    }
}

int main() {
    vector<int> arr = {12, 11, 13, 99, 22, 7,15};
    mergeSort(arr, 0, arr.size() - 1);
    for (int i : arr)
        cout << i << " ";
    return 0;
}