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
const int N = 1e6, mod = 998244353, inf = 1e18 + 5;
int ksm(int a, int b) {
    int res = 1;
    a %= mod;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

void solve(){
    int n; cin >> n;
    vector<vii> adj(n+1);
    for(int i = 1; i < n; i++){
        int u,v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vii dep(n+1), fa(n+1);
    vii mn_yz(n+1, inf), mn1(n+1, inf), mn2(n+1, inf), best(n+1);
    vector<int> vis(n+1);
    vii yz;
    auto dfs = [&](auto& self, int u, int p, int d) -> void {
        dep[u] = d;
        fa[u] = p;
        bool ok = 0; // 有没有孩子
        for (int v : adj[u]) {
            if (v == p) continue;
            ok = 1;
            self(self, v, u, d+1);
            int mn = mn_yz[v];
            if(mn < mn1[u]){
                mn2[u] = mn1[u];
                mn1[u] = mn;
                best[u] = v;
            }else if(mn < mn2[u]){
                mn2[u] = mn;
            }
        }
        if(ok == 0 && u != 1){
            vis[u] = 1;
            mn_yz[u] = d;
            yz.pb(u);
        }else {
            mn_yz[u] = mn1[u];
        }
    };
    dfs(dfs, 1, 0, 0);
    int nlp = 0, nlq = 1; // 奶龙最大概率p/q
    for(int a: yz){
        int llp = 1, llq = 1; // 噜噜最小概率p/q
        int cur = a;
        while(fa[cur] != 0){
            int w = fa[cur];
            int mn;
            if(cur == best[w]) mn = mn2[w];
            else mn = mn1[w];
            if(mn != inf){
                int p = mn - dep[w];
                int q = dep[a] - dep[w] + mn - dep[w];
                if(p * llq < llp * q){
                    llp = p;
                    llq = q;
                }
            }
            cur = w;
        }
        if(llp * nlq > nlp * llq){
            nlp = llp;
            nlq = llq;
        }
    }
    int ans = nlp % mod * ksm(nlq % mod, mod - 2) % mod;
    cout << ans << endl;
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