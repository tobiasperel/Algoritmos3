#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int longitud;
vector<int> pasos;
void cambiarLetras(string &p1, string &p2)
{

    // vector<bool> sonIguales(p1.size(), false);
    // for (int i = 0; i < p1.size(); i++)
    // {
    //     if (p1[i] != p2[i])
    //     {
    //         sonIguales[i] = true
    //     }
    // }

    int posicionAArriba = -1;
    int posicionBArriba = -1;
    int posicionAAbajo = -1;
    int posicionBAbajo = -1;

    for (int i = 0; i < p1.size(); i++)
    {
        if (p1[i] != p2[i])
        {
            if (p1[i] == 'a')
            {
                if (posicionAArriba != -1)
                {
                    pasos.push_back(posicionAArriba+1);
                    pasos.push_back(i+1);
                    posicionAArriba = -1;
                    posicionBArriba = -1;
                }
                else
                {
                    posicionAArriba = i;
                    posicionBArriba = i;
                }
            }
            else
            {
                if (posicionAAbajo != -1)
                {
                    pasos.push_back(posicionAAbajo+1);
                    pasos.push_back(i+1);
                    posicionAAbajo = -1;
                    posicionBAbajo = -1;
                }
                else
                {
                    posicionAAbajo = i;
                    posicionBAbajo = i;
                }
            }
        }
    }
    if(posicionAAbajo != -1){
        pasos.push_back(posicionAAbajo+1);
        pasos.push_back(posicionBAbajo+1);
        pasos.push_back(posicionAAbajo+1);
        pasos.push_back(posicionBArriba+1);
    }
    
}
int main()
{

    cin >> longitud;
    string p1, p2;
    cin >> p1;
    cin >> p2;
    int a1 = 0;
    int a2 = 0;
    int b1 = 0;
    int b2 = 0;

    for (int i = 0; i < longitud; i++)
    {
        if (p1[i] == 'a')
        {
            a1++;
        }
        else
        {
            b1++;
        }
        if (p2[i] == 'a')
        {
            a2++;
        }
        else
        {
            b2++;
        }
    }
    if ((a1 + a2) % 2 == 1 || (b1 + b2) % 2 == 1)
    {
        cout << -1; // Error de entrada. No es una permut
    }
    else
    {
        cambiarLetras(p1, p2);
        cout << pasos.size() / 2 << endl;
        for (int i = 0; i < pasos.size(); i += 2)
        {
            cout << pasos[i] << " " << pasos[i + 1] << endl;
        }
        
    }
    return 0;
}