#include<iostream>
#include<vector>
using namespace std;

int calcularBacktracking(int n, int k){
    if(k==0 || n == k){
        return 1;
    }
    return calcularBacktracking(n-1, k-1) + calcularBacktracking(n-1,k);
}
int calcularDinamica(vector<vector<int>> &dp, int n, int k){
    if(k==0 || n == k){
        return 1;
    }
    if(dp[n-1][k-1] == -1){
        dp[n-1][k-1] = calcularDinamica(dp,n-1,k-1) + calcularDinamica(dp,n-1,k);
    }
    
    return dp[n-1][k-1];
}
int main(){
    // cout<<calcularBacktracking(5,2);
    vector<vector<int>> dp(5, vector<int>(2,-1));
    cout<<calcularDinamica(dp,5,2);
    return 0;
}