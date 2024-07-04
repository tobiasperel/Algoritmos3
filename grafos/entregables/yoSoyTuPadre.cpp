#include <bits/stdc++.h>
using namespace std;

long long n,grafs[500][500],orden[500],suma=0;

long long FloydWarshall(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                grafs[j][k]=min(grafs[j][k],grafs[j][orden[i]]+grafs[orden[i]][k]);
            }
        }
        
        for(int j=0;j<=i;j++){
            for(int k=0;k<=i;k++){
                suma+=grafs[orden[j]][orden[k]];
            }        
        }
        cout<<suma<<" ";
    }
    return suma;
}
int main(){

    int t;
    cin>>t;
    for(int i=0;i<t;i++){
        cin>>n;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cin>>grafs[i][j];
            }
        }
        for(int i=1;i<=n;i++){
            cin>>orden[n-i];
        }
        cout<<FloydWarshall()<<"\n";
        suma = 0;
    }
    return 0;
}
