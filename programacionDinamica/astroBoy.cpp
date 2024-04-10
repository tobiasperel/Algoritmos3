#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<vector<int>>memo;
int astroBoyTopDown(int n,int c){
    if(n < 0){
        return -INT_FAST16_MIN;
    }
    if(c < 0){
        return -INT_FAST16_MIN;
    }
    if(n == 0){
        return 0;
    }
    if(memo[n-1][c+1] == -1){
        memo[n-1][c+1] = astroBoyTopDown(n-1,c+1);
    }
    if(memo[n-1][c] == -1){
        memo[n-1][c] = astroBoyTopDown(n-1,c);
    }
    if(memo[n-1][c-1] == -1){
        memo[n-1][c-1] = astroBoyTopDown(n-1,c-1);
    }
    return max(max(memo[n-1][c+1], memo[n-1][c]), memo[n-1][c-1]);
    
}

int main(){
    int n,c; // n is the number days & c is the number of asteroids
    cin>>n;
    cin>>c; 
    vector<int>asteroids;
    for(int i = 0; i<c;i++){
        int asteroid;
        cin>>asteroid;
        asteroids.push_back(asteroid);
    }
    for(int i = 0; i<n;i++){
        vector<int>temp;
        for(int j = 0; j<c;j++){
            temp.push_back(-1);
        }
        memo.push_back(temp);
    }
    cout<<astroBoyTopDown(n,c);
}