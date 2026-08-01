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
const int N = 5e5 + 5, mod = 1e9+7, inf = 1e18 + 5;

void solve(){
    int n; cin >> n;
    vector<int> p(n+1);
    rep(i,1,n) cin >> p[i];
    vector<vector<int>> adj(n+1);
    vector<int> fa(n+1), dep(n+1), mask(n+1);
    for(int i = 2; i <= n; i++){
        int p; char c;
        cin >> p >> c;
        adj[p].pb((int)i);
        fa[i] = (int)p;
        dep[i] = dep[p] + 1;
        mask[i] = mask[p] ^ (1 << (c - 'a'));
    }

    vector<int> siz(n+1,1), big(n+1);
    for(int u = n; u >= 2; u--){
        int p = fa[u];
        siz[p] += siz[u];
        if(big[p] == 0 || siz[u] > siz[big[p]]){
            big[p] = (int)u;
        }
    }

    vector<array<int,3>> ans(n+1, array<int,3>{-1,-1,-1});
    rep(i,1,n) ans[i][0] = 0;
    static int mx[1 << 22][3];
    memset(mx,-1,sizeof(mx));
    auto query = [&](int x, int root) -> void {
        int s = mask[x];
        auto check = [&](int tar) -> void {
            rep(rem,0,2){
                if(mx[tar][rem] == -1) continue;
                int len = dep[x] + mx[tar][rem] - 2 * dep[root];
                ans[root][len % 3] = max(ans[root][len % 3],len);
            }
        };
        check(s);
        for(int bit = 0; bit <= 21; bit++){
            check(s ^ (1 << bit));
        }
    };

    auto change = [&](int st, int op, int root = 0) -> void {
        vector<int> stk;
        stk.pb(st);
        while(!stk.empty()){
            int u = stk.back();
            stk.pop_back();
            if(op == 0){
                query(u,root);
            }
            else if(op == 1){
                int rem = dep[u] % 3;
                mx[mask[u]][rem] = max(mx[mask[u]][rem],dep[u]);
            }
            else{
                mx[mask[u]][dep[u] % 3] = -1;
            }
            for(int v : adj[u]){
                stk.pb(v);
            }
        }
    };

    auto dsu = [&](auto& self, int u, int keep) -> void {
        for(int v : adj[u]){
            if(v == big[u]) continue;
            self(self,v,0);
        }
        if(big[u] != 0) self(self,big[u],1);
    
        for(int v : adj[u]){
            rep(rem,0,2){
                ans[u][rem] = max(ans[u][rem],ans[v][rem]);
            }
        }
        query(u,u);
        int rem = dep[u] % 3;
        mx[mask[u]][rem] = max(mx[mask[u]][rem],dep[u]);
        for(int v : adj[u]){
            if(v == big[u]) continue;
            change(v,0,u);
            change(v,1);
        }
        if(keep == 0) change(u,-1);
    };

    dsu(dsu,1,0);

    for(int i = 1; i <= n; i++){
        cout << ans[i][p[i]] << " \n"[i==n];
    }
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