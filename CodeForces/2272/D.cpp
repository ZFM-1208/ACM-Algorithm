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
    int k; cin >> k;
    vii siz(k+1);
    vector<vector<pii>> e(k+1);
    for(int i = 1; i <= k; i++){
        int n; cin >> n;
        siz[i] = n;
        for(int j = 1; j < n; j++){
            int u,v; cin >> u >> v;
            e[i].pb({u,v});
        }
    }
    int op = -1;
    for(int i = 1; i <= k; i++){
        if(siz[i] > 1){
            op = i;
            break;
        }
    }
    if(op == -1){
        for(int i = 2; i <= k; i++){
            cout << 1 << " " << 1 << " " << i << " " << 1 << endl;
        }
        return;
    }
    int n = siz[op];
    vector<vii> adj(n+1);
    for(auto [u,v]: e[op]){
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vector<vii> dp(n+1,vii(2));
    auto dfs = [&](auto&self, int u, int p) -> void {
        dp[u][0] = 0;
        dp[u][1] = 1;
        for(int v : adj[u]){
            if(v == p) continue;
            self(self, v, u);
            dp[u][0] += max(dp[v][0], dp[v][1]);
            dp[u][1] += dp[v][0];
        }
    };

    dfs(dfs,1,0);
    int base;
    if(dp[1][0] >= dp[1][1]) {
        base = 1;
    }else{
        base = adj[1][0];
    }
    for(int i = 1; i <= k; i++){
        if(i == op) continue;
        cout << op << " " << base << " " << i << " " << 1 << endl;
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();
    return 0;
}