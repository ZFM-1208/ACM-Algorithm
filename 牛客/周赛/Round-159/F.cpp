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

struct BIT {
    int n;
    vector<int> tr;
    BIT(int _n) : n(_n), tr(_n + 1, 0) {}
    int lowbit(int x) { return x & -x; }
    
    void add(int x, int c) {
        c = (c % mod + mod) % mod;
        for (int i = x; i <= n; i += lowbit(i)) tr[i] = (tr[i] + c) % mod;
    }
    
    int query(int x) {
        int res = 0;
        for (int i = x; i > 0; i -= lowbit(i)) res = (res + tr[i]) % mod;
        return res;
    }
    
    int query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};


void solve(){
    int n,q; cin >> n >> q;
    string s; cin >> s;
    s = " " + s;
    vector<vii> g(n+1);
    for(int i = 1; i < n; i++){
        int u, v; cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    vii pw2(n+2);
    pw2[0] = 1;
    rep(i, 1, n){
        pw2[i] = (pw2[i - 1] * 2) % mod;
    }
    vector<int> dep(n + 1), dfn(n + 1), out(n + 1);
    // vector<vector<int>> fa(n + 1, vector<int>(25));
    int ti = 0;
    dep[0] = -1;
    auto dfs = [&](auto& self, int u, int p) -> void {
        dfn[u] = ++ti;
        dep[u] = dep[p] + 1;
        // fa[u][0] = p;
        // for (int i = 1; i <= 20; i++) {
        //     fa[u][i] = fa[fa[u][i - 1]][i - 1];
        // }
        for (int v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
        }
        out[u] = ti;
    };
    dfs(dfs, 1, 0);

    BIT bit(n+2);
    for(int i = 1; i <= n; i++){
        if(s[i] == '1'){
            bit.add(dfn[i], pw2[dep[i]]);
            bit.add(out[i] + 1, -pw2[dep[i]]);
        }
    }
    while(q--){
        char op; cin >> op;
        int u; cin >> u;
        if(op == 'F'){
            if(s[u] == '1'){
                s[u] = '0';
                bit.add(dfn[u], -pw2[dep[u]]);
                bit.add(out[u] + 1, pw2[dep[u]]);
            }else{
                s[u] = '1';
                bit.add(dfn[u], pw2[dep[u]]);
                bit.add(out[u] + 1, -pw2[dep[u]]);
            }
        }else{
            cout << bit.query(dfn[u]) << endl;
        }
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