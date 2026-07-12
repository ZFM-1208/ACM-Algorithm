#include<bits/stdc++.h>
using namespace std;
#define rep(i, l, r) for (int i = l; i <= r; i++)
#define vii vector<int>
#define pii pair<int, int>
#define int long long
#define pb push_back
#define fi first
#define se second
#define endl '\n'
double pi = acos(-1);
const int N = 1e6, mod = 1e9+7, inf = 1e18 + 5;

void solve(){
    int n; cin >> n;
    vector<int> du(n+1);
    for(int i = 0; i < n; i++){
        int u, v;
        cin >> u >> v;
        du[u]++;
        du[v]++;
    }
    int p1 = -1;
    int p2 = -1;
    for(int i = 1; i <= n; i++){
        if(du[i] == 1){
            p1 = i;
        }else if(du[i] == 3){
            p2 = i;
        }
    }
    cout << p2 << " " << p1 << "\n";
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    return 0;
}