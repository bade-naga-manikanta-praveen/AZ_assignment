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
                for(int k=0;k<=m;k++){
                    dp[i][j][k]=1e18;
                }
            }
        }
        //base case
        if(a[0]!=0){
            dp[0][1][a[0]]=0;
        }
        else{
            for(int i=1;i<=m;i++){
                dp[0][1][i]=p[0][i];
            }
        }
        debarr(dp[0][1],m+1);
        //transition
        for(int i=1;i<n;i++){
            for(int j=1;j<=n;j++){
                pr(i,j);
                //calculate prefixes
                int mn1,ind1,mn2,ind2;
                auto it=min_element(dp[i-1][j]+1,dp[i-1][j]+m+1);
                ind1=it-dp[i-1][j];
                mn1=*it;
                mn2=2e18;
                for(int k=1;k<=m;k++){
                    if(ind1==k) continue;
                    if(dp[i-1][j][k]<mn2){
                        mn2=dp[i-1][j][j];
                        ind2=k;
                    }
                }
                debarr(dp[i][j],m+1);
                pr(mn1,mn2,ind1,ind2);
                //transition
                for(int k=1;k<=m;k++){
                    if(a[k]==0){
                        dp[i][j][k]=min(dp[i][j][k],p[i][k]+dp[i-1][j][k]);
                        if(k==ind1){
                            dp[i][j][k]=min(dp[i][j][k],p[i][k]+mn2);
                        }
                        else{
                            dp[i][j][k]=min(dp[i][j][k],p[i][k]+mn1);
                        }
                    }
                    else if(k==a[k]){
                        dp[i][j][k]=min(dp[i][j][k],dp[i-1][j][k]);
                        if(k==ind1){
                            dp[i][j][k]=min(dp[i][j][k],mn2);
                        }
                        else{
                            dp[i][j][k]=min(dp[i][j][k],mn1);
                        }
                    }
                }
            }
        }
        int ans=1e18;
        pr(n-1,k);
        for(int i=1;i<=m;i++){
         
            ans=min(ans,dp[n-1][k][i]);
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