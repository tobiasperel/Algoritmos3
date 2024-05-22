#include <iostream>
#include <vector>
#include <algorithm>

// Función auxiliar para encontrar el dígito en la posición específica
int obtenerDigito(int num, int pos) {
    for (int i = 1; i < pos; ++i)
        num /= 10;
    return num % 10;
}

// Función para obtener el número de dígitos del número más grande en el vector
int obtenerNumeroDigitosMax(const std::vector<int>& arr) {
    int max = *std::max_element(arr.begin(), arr.end());
    int digitos = 0;
    while (max != 0) {
        max /= 10;
        ++digitos;
    }
    return digitos;
}

// Función principal de Radix Sort
void radixSort(std::vector<int>& arr) {
    int digitos = obtenerNumeroDigitosMax(arr);
    std::vector<std::vector<int>> cubeta(10);

    // Ordena el arreglo basado en el dígito actual
    for (int d = 1; d <= digitos; ++d) {
        for (int num : arr) {
            int digito = obtenerDigito(num, d);
            cubeta[digito].push_back(num);
        }

        // Reemplaza el arreglo original con los números ordenados por el dígito actual
        arr.clear();
        for (int i = 0; i < 10; ++i) {
            arr.insert(arr.end(), cubeta[i].begin(), cubeta[i].end());
            cubeta[i].clear();
        }
    }
}

// Función para imprimir un vector
void imprimirVector(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};
    
    std::cout << "Arreglo original: ";
    imprimirVector(arr);

    radixSort(arr);

    std::cout << "Arreglo ordenado: ";
    imprimirVector(arr);

    return 0;
}
