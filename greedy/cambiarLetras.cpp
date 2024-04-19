#include <iostream>
#include <vector>
using namespace std;

int longitud;
vector<int> pasos;

void cambiarLetras(string p1, string p2) {
  for (int i = 0; i < longitud; i++) {

    if (p1[i] == p2[i]) {
      continue;
    }
    if (p1[i] != p2[i + 1]) {
      char aux = p1[i];
      p1[i] = p2[i + 1];
      p2[i + 1] = aux;
      pasos.push_back(i + 1);
      pasos.push_back(i + 2);
    }
  }
}

void nivelar(string &p1, string &p2, int cantidadDeCambios, bool masAEnp1) {
  for (int i = 0; i < longitud; i++) {
    if (p1[i] != p2[i] && cantidadDeCambios > 0) {
      cantidadDeCambios--;
      if ((p1[i] == 'a' && masAEnp1) || (p1[i] == 'b' && masAEnp1 == false)) {
        char aux = p2[i];
        p2[i] = p1[i];
        p1[i] = aux;
        pasos.push_back(i);
        pasos.push_back(i);
      }
    }
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
    if (a1 == a2 && b1 == b2) {
      // cambiarLetras(p1, p2);
    } else {
      nivelar(p1, p2, abs(a1 - a2 / 2), a1 > a2);
      // cambiarLetras(p1, p2);
    }
    cout << pasos.size() / 2 << endl;
    for (int i = 0; i < pasos.size(); i += 2) {
      cout << pasos[i] << " " << pasos[i + 1] << endl;
    }
    cout << p1 << endl << p2;
  }
  return 0;
}