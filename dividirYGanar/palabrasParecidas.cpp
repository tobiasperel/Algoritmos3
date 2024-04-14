#include<iostream>
#include<string>

using namespace std;

bool mejorPalabra(string a,string b){
    int longitud=a.length();

    if(a==b) return true;
    if(longitud%2!=0)    return false;

    string a1=a.substr(0,longitud/2);
    string a2=a.substr(longitud/2,longitud/2);
    string b1=b.substr(0,longitud/2);
    string b2=b.substr(longitud/2,longitud/2);

    if((mejorPalabra(a1,b2)&&mejorPalabra(a2,b1)) ||  (mejorPalabra(a1,b1)&&mejorPalabra(a2,b2)) )  return true;
    return false;    
}


int main(){
    
    string a,b;
    cin>>a>>b;
    if(mejorPalabra(a,b)){
        cout<<"YES";
    }
    else {
        cout<<"NO";
    }
    return 0;
}