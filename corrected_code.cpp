#include <bits/stdc++.h>
using namespace std;
#define int long long
int dp[105][105][105];
int a[105];

int32_t main(){
    int _t;
    cin>>_t;
    while(_t--){
        int n,m,k;
        cin>>n>>m>>k;
        for(int i=0;i<n;i++){
            cin>>a[i];
        }
        int p[n][m+1];
        for(int i=0;i<n;i++){
            for(int j=1;j<=m;j++){
                cin>>p[i][j];
            }
        }
        
        // Initialize DP
        for(int i=0;i<=n;i++){
            for(int j=0;j<=k;j++){
                for(int col=0;col<=m;col++){
                    dp[i][j][col]=1e18;
                }
            }
        }
        
        // Base case: first tree
        if(a[0]!=0){
            dp[0][1][a[0]]=0;
        }
        else{
            for(int col=1;col<=m;col++){
                dp[0][1][col]=p[0][col];
            }
        }
        
        // DP transition
        for(int i=1;i<n;i++){
            for(int j=1;j<=min(i+1,k);j++){
                for(int col=1;col<=m;col++){
                    // Case 1: Same color as previous tree (beauty doesn't increase)
                    if(a[i]==0 || a[i]==col){
                        int cost = (a[i]==0) ? p[i][col] : 0;
                        dp[i][j][col] = min(dp[i][j][col], dp[i-1][j][col] + cost);
                    }
                    
                    // Case 2: Different color from previous tree (beauty increases)
                    if(j > 1){
                        for(int prev_col=1;prev_col<=m;prev_col++){
                            if(prev_col != col){
                                if(a[i]==0 || a[i]==col){
                                    int cost = (a[i]==0) ? p[i][col] : 0;
                                    dp[i][j][col] = min(dp[i][j][col], dp[i-1][j-1][prev_col] + cost);
                                }
                            }
                        }
                    }
                }
            }
        }
        
        // Find answer
        int ans=1e18;
        for(int col=1;col<=m;col++){
            ans=min(ans,dp[n-1][k][col]);
        }
        
        if(ans>=1e18){
            cout<<"-1"<<"\n";
        }
        else{
            cout<<ans<<"\n";
        }
    }
    return 0;
}