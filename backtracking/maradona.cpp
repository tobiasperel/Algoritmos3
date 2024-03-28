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
vector<vector<jugador>> ganadores;

bool compareFormations(const vector<jugador>& a, const vector<jugador>& b) {
        return a[0].nombre < b[0].nombre;
}

void bubbleSort1(vector<jugador> &ganadorProvisorio)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 4 - i; j++)
        {
            if (ganadorProvisorio[j].nombre > ganadorProvisorio[j + 1].nombre)
            {
                jugador temp = ganadorProvisorio[j];
                ganadorProvisorio[j] = ganadorProvisorio[j + 1];
                ganadorProvisorio[j + 1] = temp;
            }
        }
    }
}

void bubbleSort2(vector<jugador> &ganadorProvisorio){
    for (int i = 5; i < 10; i++)
    {
        for (int j = 5; j < 14 - i; j++)
        {
            if (ganadorProvisorio[j].nombre > ganadorProvisorio[j + 1].nombre)
            {
                jugador temp = ganadorProvisorio[j];
                ganadorProvisorio[j] = ganadorProvisorio[j + 1];
                ganadorProvisorio[j + 1] = temp;
            }
        }
    }
}

void encontrarMejorFormacion(vector<jugador>jugadores , vector<jugador> &parcial,int sumaAtacantes, int sumaDefensa, int index)
{

    if (parcial.size() == 5)
    {
        if (sumaAtacantes > recordAtaque ||
            (sumaAtacantes == recordAtaque) & (sumaDefensa < recordDefensa) || (sumaAtacantes == recordAtaque && sumaDefensa == recordDefensa &&  compareFormations(parcial, ganadorProvisorio)   ) ){
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
    for (int caso = 0; caso < casos; caso++){
        for (int i = 0; i < 10; i++)
        {
            string nombre; // Add this line
            cin >> nombre; // Change jugador.name to nombre

            cin >> ataque;
            cin >> defensa;
            jugadores.push_back(jugador{nombre, ataque, defensa});
        }
        
        encontrarMejorFormacion(jugadores, parcial, 0, 0, 0);
        bubbleSort1(ganadorProvisorio);
        
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
        
        bubbleSort2(ganadorProvisorio);
        string formacionDelanteros = "(";
        for (int i = 0; i < 5; i++)
        {
            if (i == 4){
                formacionDelanteros += ganadorProvisorio[i].nombre + ")";
                break;
            }
            formacionDelanteros += ganadorProvisorio[i].nombre + ", ";
            
        }
        string formacionDefensores = "(";
        for (int i = 5; i < 10; i++)
        {
            if (i == 9){
                formacionDefensores += ganadorProvisorio[i].nombre + ")";
                break;
            }
            formacionDefensores += ganadorProvisorio[i].nombre + ", ";
        }
        cout <<"Case " + to_string(caso + 1) + ":" << endl << formacionDelanteros << endl << formacionDefensores;
        recordAtaque = 0;
        recordDefensa = 0;
        jugadores.clear();
        ganadorProvisorio.clear();

    }    
    return 0;
}