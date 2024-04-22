#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int longitud;
vector<int> pasos;
void cambiarLetras(string &p1, string &p2)
{

    vector<bool> p1A(p1.size(),false);
    vector<bool> p2A(p2.size(),false);
    for (int i = 0; i < p1.size(); i++)
    {
        if (p1[i] != p2[i])
        {
            if (p1[i] == 'a')
            {
                p1A[i] = true;
            }
            else
            {
                p2A[i] = true;
            }
        }
    }
    queue<int>interinA;
    queue<int>interinB;
    for (int i = 0; i < p1.size(); i++)
    {
        if (p1[i] != p2[i])
        {
            if(p1A[i] == true){
                if(interinB.empty()){
                    interinA.push(i);
                }
                else{
                    char aux = p2[interinB.front()];
                    p2[interinB.front()] = p1[i];
                    p1[i] = aux;
                    pasos.push_back(i);
                    pasos.push_back(interinB.front());
                    interinA.pop();
                    interinB.pop();
                    
                }
            }
            else{
                if(interinA.empty()){
                    interinB.push(i);
                }
                else{
                    char aux = p2[interinA.front()];
                    p2[interinA.front()] = p1[i];
                    p1[i] = aux;
                    pasos.push_back(i);
                    pasos.push_back(interinA.front());
                    interinA.pop();
                    interinB.pop();
                    
                }
            }
        }
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
        cout << p1 << endl
             << p2;
    }
    return 0;
}