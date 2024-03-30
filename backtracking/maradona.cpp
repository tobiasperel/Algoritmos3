#include <iostream>
#include <vector>
#include<algorithm>
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

bool compareFormations(vector<jugador> a, vector<jugador> b) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for (int i = 0; i < 5; i++) {
        if (a[i].nombre < b[i].nombre) {
            return true;
        }
    }
    return false;
}

vector<bool> esDelanteroParcial (10,false);
vector<bool> esDelanteroDef (10,false);

void encontrarMejorFormacion(vector<jugador>jugadores , vector<jugador> &parcial,int sumaAtacantes, int sumaDefensa, int index)
{

    if (parcial.size() == 5)
    {
        if (sumaAtacantes > recordAtaque ||
            (sumaAtacantes == recordAtaque) && (sumaDefensa < recordDefensa) || (sumaAtacantes == recordAtaque && sumaDefensa == recordDefensa &&  compareFormations(parcial, ganadorProvisorio)   ) ){
            recordAtaque = sumaAtacantes;
            recordDefensa = sumaDefensa;
            ganadorProvisorio = parcial;
            esDelanteroDef = esDelanteroParcial;
        }
        return;
    }
    for (int i = index; i < 10; i++)
    {
        parcial.push_back(jugadores[i]);
        esDelanteroParcial[i] = true;
        encontrarMejorFormacion(jugadores, parcial,
                                sumaAtacantes + jugadores[i].ataque, sumaDefensa + jugadores[i].defensa,
                                i + 1);
        parcial.pop_back();
        esDelanteroParcial[i] = false;
    }
}

int main()
{
    int casos;
    cin >> casos;
    string nombre;
    int ataque;
    int defensa;
    string superFrase;
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
        sort(ganadorProvisorio.begin(), ganadorProvisorio.end()); 
        
        // agergar a los 5 jugadores restantes
        for (int i=0; i <10;i++){
            if (!esDelanteroDef[i]){
                ganadorProvisorio.push_back(jugadores[i]);
            }
        }
        sort(ganadorProvisorio.begin()+5, ganadorProvisorio.end());
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
        superFrase += "Case " + to_string(caso + 1) + ":" + "\n" + formacionDelanteros + "\n" + formacionDefensores+ "\n";
        recordAtaque = 0;
        recordDefensa = 0;
        jugadores.clear();
        ganadorProvisorio.clear();
        parcial.clear();
        formacionDefensores.clear();
        formacionDelanteros.clear();

    }    
    cout << superFrase;
    return 0;
}