#include <iostream>
#include <vector>
using namespace std;

int recordAtaque = 0;
int recordDefensa = 0;


struct jugador
{
    string nombre;
    int ataque;
    int defensa;
    bool operator<(const jugador& other) const {
        return nombre < other.nombre;
    }
};

vector<jugador> jugadores;
vector<jugador> ganadorProvisorio;


bool compareFormations(const vector<jugador>& a, const vector<jugador>& b) {
        return a[0].nombre < b[0].nombre;
}

void bubbleSort(vector<jugador> &jugadores, int posicion)
{
    for (int i = 0+posicion; i < 5+posicion; i++)
    {
        for (int j = 0+posicion; j < 4 - i+posicion; j++)
        {
            if (jugadores[j].nombre > jugadores[j + 1].nombre)
            {
                jugador temp = jugadores[j];
                jugadores[j] = jugadores[j + 1];
                jugadores[j + 1] = temp;
            }
        }
    }
}


void encontrarMejorFormacion(vector<jugador>jugadores , vector<jugador> &parcial,int sumaAtacantes, int sumaDefensa, int index)
{

    if (parcial.size() == 5)
    {
        if (sumaAtacantes > recordAtaque ||
            (sumaAtacantes == recordAtaque) & (sumaDefensa > recordDefensa) || (sumaAtacantes == recordAtaque && sumaDefensa == recordDefensa &&  compareFormations(parcial, ganadorProvisorio)   ) ){
            recordAtaque = sumaAtacantes;
            recordDefensa = sumaDefensa;
            ganadorProvisorio = parcial;
        }
        return;
    }
    for (int i = index; i < 10; i++)
    {
        parcial.push_back(jugadores[i]);
        encontrarMejorFormacion(jugadores, parcial,
                                sumaAtacantes + jugadores[i].ataque, sumaDefensa + jugadores[i].defensa,
                                i + 1);
        parcial.pop_back();
    }
}

int main()
{
    int casos;
    cin >> casos;
    string nombre;
    int ataque;
    int defensa;
    vector<jugador> parcial; // Add this line

    for (int i = 0; i < 10; i++)
    {
        string nombre; // Add this line
        cin >> nombre; // Change jugador.name to nombre
        cin >> ataque;
        cin >> defensa;
        jugadores.push_back(jugador{nombre, ataque, defensa});
    }
    
    encontrarMejorFormacion(jugadores, parcial, 0, 0, 0);
    bubbleSort(ganadorProvisorio,0);

    // agergar a los 5 jugadores restantes
    for (int i=0; i <10;i++){
        bool found = false;
        for (int j=0; j<10;j++){
            if (jugadores[i].nombre == ganadorProvisorio[j].nombre){
                found = true;
                break;
            }
        }
        if (!found){
            ganadorProvisorio.push_back(jugadores[i]);
        }
    }

    bubbleSort(ganadorProvisorio,5);
    cout << "Mejor formacion: ";
    for (int i = 0; i < 10; i++)
    {
        cout << ganadorProvisorio[i].nombre << " ";
    }
    return 0;
}