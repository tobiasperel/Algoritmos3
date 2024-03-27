#include <iostream>
#include <vector>
using namespace std;

int recordAtaque = 0;
int recordDefensa = 0;
vector<string> ganadorProvisorio;

void encontrarMejorFormacion(vector<string> nombres, vector<int> ataque,
                             vector<int> defensa, vector<string> &parcial,
                             int sumaAtacantes, int sumaDefensa, int index) {
  if (parcial.size() == 5) {
    if (sumaAtacantes > recordAtaque ||
        (sumaAtacantes == recordAtaque) & (sumaDefensa > recordDefensa)) {
      recordAtaque = sumaAtacantes;
      recordDefensa = sumaDefensa;
      ganadorProvisorio = parcial;
    }
    return;
  }
  for (int i = index; i < 10; i++) {
    parcial.push_back(nombres[i]);
    encontrarMejorFormacion(nombres, ataque, defensa, parcial,
                            sumaAtacantes + ataque[i], sumaDefensa + defensa[i],
                            i + 1);
    parcial.pop_back();
  }
}

int main() {
  int casos;
  cin >> casos;
  vector<string> nombres;
  vector<int> ataque;
  vector<int> defensa;
  string nombre;
  int score;
  vector<string> parcial; // Add this line

  for (int i = 0; i < 10; i++) {
    cin >> nombre;
    nombres.push_back(nombre);
    cin >> score;
    ataque.push_back(score);
    cin >> score;
    defensa.push_back(score);
  }
  int sumaTotal = 0;
  for (int i = 0; i < 10; i++) {
    sumaTotal += ataque[i];
  }
  encontrarMejorFormacion(nombres, ataque, defensa, parcial, 0, 0, 0);
  cout << "Mejor formación: ";
  for (int i = 0; i < 5; i++) {
    cout << ganadorProvisorio[i] << " ";
  }
  return 0;
}