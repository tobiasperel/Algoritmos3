#include<iostream>
#include<vector>
using namespace std;

// complejidad de tiempo O(n)

void hornersRule(){
    vector<int>coheficientes = {1,2,3,4,5}; // f(x) = x^4 + 2x^3 + 3x^2 + 4x + 5 --> 5 + x(4 + x(3 + x(2 + x(1)))) 
    int x = 2;
    int result = coheficientes[0];
    for(int i=1; i<coheficientes.size();i++){
        result = result*x + coheficientes[i];
    }
    cout<<result;
}

int main(){
    hornersRule();

}