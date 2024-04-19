#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int longitud;
vector<int> pasos;
vector<int> poscionesABorrar;
void cambiarLetras(string &p1, string &p2) {
  for (int i = 0; i < longitud; i++) {
    if (p1[i] == p2[i]) {
      poscionesABorrar.push_back(i);
      continue;
    }
  }
  for (int i = 0; i < poscionesABorrar.size(); i++) {
    p1.erase(poscionesABorrar[i], 1);
    p2.erase(poscionesABorrar[i], 1);
  }
  for (int i = 0; i < p1.size(); i++) {
    if (p1[i] != p2[i + 1]) {
      char aux = p1[i];
      p1[i] = p2[i + 1];
      p2[i + 1] = aux;
      pasos.push_back(i + 1);
      pasos.push_back(i + 2);
    }
  }

  int main() {

    cin >> longitud;
    string p1, p2;
    cin >> p1;
    cin >> p2;
    int a1 = 0;
    int a2 = 0;
    int b1 = 0;
    int b2 = 0;

    for (int i = 0; i < longitud; i++) {
      if (p1[i] == 'a') {
        a1++;
      } else {
        b1++;
      }
      if (p2[i] == 'a') {
        a2++;
      } else {
        b2++;
      }
    }
    if ((a1 + a2) % 2 == 1 || (b1 + b2) % 2 == 1) {
      cout << -1; // Error de entrada. No es una permut
    } else {
      cambiarLetras(p1, p2);
      cout << pasos.size() / 2 << endl;
      for (int i = 0; i < pasos.size(); i += 2) {
        cout << pasos[i] << " " << pasos[i + 1] << endl;
      }
      cout << p1 << endl << p2;
    }
    return 0;
  }