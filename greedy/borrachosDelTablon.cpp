#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int longitud;
vector<int> pasos;
vector<int> poscionesABorrar;
void cambiarLetras(string &p1, string &p2) {
  queue<int> p1_queue;
  queue<int> p2_queue;
  vector<int> indiceRepresenta1;
  vector<int> indiceRepresenta2;
  for (int i = 0; i < p1.size(); i++) {
    if (p1[i] != p2[i]) {
      if (p1[i] == 'a') {
        p1_queue.push(i);
        indiceRepresenta1.push_back(i);
      } else {
        p2_queue.push(i);
        indiceRepresenta2.push_back(i);
      }
    }
  }
  for (int i = 0; i < min(p1_queue.size(), p2_queue.size()); i++) {
    if (p1[i] != p2[i]) {
      if (p1[i] == 'b') {
        p1[i] = 'a';
        p2_queue.pop();
        pasos.push_back(i);
        pasos.push_back(indiceRepresenta1[i]);
      } else {
        p2[i] = 'a';
        p1_queue.pop();
        pasos.push_back(i);
        pasos.push_back(indiceRepresenta2[i]);
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
    cambiarLetras(p1, p2);
    cout << pasos.size() / 2 << endl;
    for (int i = 0; i < pasos.size(); i += 2) {
      cout << pasos[i] << " " << pasos[i + 1] << endl;
    }
    cout << p1 << endl << p2;
  }
  return 0;
}