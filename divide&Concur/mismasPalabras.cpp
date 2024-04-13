#include <iostream>
#include <string>

using namespace std;

bool sonEquivalentes(string a, string b) {
    int n = a.length();
    
    if (n % 2 != 0)
        return false;
    
    // Dividir las cadenas en dos partes
    string a1 = a.substr(0, n/2);
    string a2 = a.substr(n/2);
    string b1 = b.substr(0, n/2);
    string b2 = b.substr(n/2);
    
    // Caso 1: a1 es equivalente a b1, y a2 es equivalente a b2
    if ((sonEquivalentes(a1, b1) && sonEquivalentes(a2, b2)) ||
        // Caso 2: a1 es equivalente a b2, y a2 es equivalente a b1
        (sonEquivalentes(a1, b2) && sonEquivalentes(a2, b1)))
        return true;
    
    return false;
}

int main() {
    string a, b;
    cin >> a >> b;
    
    if (sonEquivalentes(a, b))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    
    return 0;
}
