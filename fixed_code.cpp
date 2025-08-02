#include <bits/stdc++.h>
using namespace std;
#define int long long
int dp[105][105][105];
int a[105];


#define debarr(a,n) cout<<#a<<" : ";for(int i=0;i<n;i++) cerr<<a[i]<<" "; cerr<<endl;
#define debmat(mat,row,col) cout<<#mat<<" :\n";for(int i=0;i<row;i++) {for(int j=0;j<col;j++) cerr<<mat[i][j]<<" ";cerr<<endl;}
#define pr(...) dbs(#__VA_ARGS__, __VA_ARGS__)
template <class S, class T>ostream& operator <<(ostream& os, const pair<S, T>& p) {return os << "(" << p.first << ", " << p.second << ")";}
template <class T>ostream& operator <<(ostream& os, const vector<T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class T>ostream& operator <<(ostream& os, const unordered_set<T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class S, class T>ostream& operator <<(ostream& os, const unordered_map<S, T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class T>ostream& operator <<(ostream& os, const set<T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class T>ostream& operator <<(ostream& os, const multiset<T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class S, class T>ostream& operator <<(ostream& os, const map<S, T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class T> void dbs(string str, T t) {cerr << str << " : " << t << "\n";}
template <class T, class... S> void dbs(string str, T t, S... s) {int idx = str.find(','); cerr << str.substr(0, idx) << " : " << t << ","; dbs(str.substr(idx + 1), s...);}
template <class T> void prc(T a, T b) {cerr << "["; for (T i = a; i != b; ++i) {if (i != a) cerr << ", "; cerr << *i;} cerr << "]\n";}


int32_t main(){
    int _t;
    _t=1;
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
        //intialise DP
        for(int i=0;i<=n;i++){
            for(int j=0;j<=n;j++){
                for(int l=0;l<=m;l++){
                    dp[i][j][l]=1e18;
                }
            }
        }
        //base case
        if(a[0]!=0){
            dp[0][1][a[0]]=0;
        }
        else{
            for(int l=1;l<=m;l++){
                dp[0][1][l]=p[0][l];
            }
        }
        debarr(dp[0][1],m+1);
        //transition
        for(int i=1;i<n;i++){
            for(int j=1;j<=min(i+1,k);j++){  // j can't exceed i+1 (beauty can't exceed number of trees)
                pr(i,j);
                //calculate prefixes - find minimum and second minimum from previous state
                int mn1,ind1,mn2,ind2;
                mn1 = 2e18; mn2 = 2e18;
                ind1 = -1; ind2 = -1;
                
                // Find minimum and second minimum
                for(int l=1;l<=m;l++){
                    if(dp[i-1][j][l] < mn1){
                        mn2 = mn1;
                        ind2 = ind1;
                        mn1 = dp[i-1][j][l];
                        ind1 = l;
                    }
                    else if(dp[i-1][j][l] < mn2){
                        mn2 = dp[i-1][j][l];
                        ind2 = l;
                    }
                }
                
                // Also consider case where beauty increases (j-1 -> j)
                if(j > 1){
                    int mn1_prev = 2e18, ind1_prev = -1, mn2_prev = 2e18, ind2_prev = -1;
                    for(int l=1;l<=m;l++){
                        if(dp[i-1][j-1][l] < mn1_prev){
                            mn2_prev = mn1_prev;
                            ind2_prev = ind1_prev;
                            mn1_prev = dp[i-1][j-1][l];
                            ind1_prev = l;
                        }
                        else if(dp[i-1][j-1][l] < mn2_prev){
                            mn2_prev = dp[i-1][j-1][l];
                            ind2_prev = l;
                        }
                    }
                    // Update mn1, mn2 if needed for color changes
                    if(mn1_prev < mn1){
                        mn2 = mn1;
                        ind2 = ind1;
                        mn1 = mn1_prev;
                        ind1 = ind1_prev;
                    }
                    else if(mn1_prev < mn2){
                        mn2 = mn1_prev;
                        ind2 = ind1_prev;
                    }
                }
                
                debarr(dp[i][j],m+1);
                pr(mn1,mn2,ind1,ind2);
                
                //transition
                for(int l=1;l<=m;l++){
                    if(a[i]==0){  // Fixed: should check a[i], not a[l]
                        // Same color case
                        dp[i][j][l]=min(dp[i][j][l],p[i][l]+dp[i-1][j][l]);
                        
                        // Different color case (beauty increases)
                        if(j > 1){
                            if(l==ind1){
                                dp[i][j][l]=min(dp[i][j][l],p[i][l]+mn2_prev);
                            }
                            else{
                                dp[i][j][l]=min(dp[i][j][l],p[i][l]+mn1_prev);
                            }
                        }
                    }
                    else if(l==a[i]){  // Fixed: should check l==a[i], not k==a[k]
                        // Same color case
                        dp[i][j][l]=min(dp[i][j][l],dp[i-1][j][l]);
                        
                        // Different color case (beauty increases)
                        if(j > 1){
                            if(l==ind1_prev){
                                dp[i][j][l]=min(dp[i][j][l],mn2_prev);
                            }
                            else{
                                dp[i][j][l]=min(dp[i][j][l],mn1_prev);
                            }
                        }
                    }
                }
            }
        }
        int ans=1e18;
        pr(n-1,k);
        for(int l=1;l<=m;l++){
            ans=min(ans,dp[n-1][k][l]);
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