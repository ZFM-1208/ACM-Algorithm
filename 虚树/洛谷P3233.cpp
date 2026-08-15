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
    vector<vii> adj(n+1);
    for(int i = 1; i < n; i++){
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vector<int> dep(n+1), dfn(n+1), out(n+1), siz(n+1);
    vector<vector<int>> fa(n+1, vector<int>(25));
    int ti = 0;
    auto dfs_lca = [&](auto& self, int u, int p) -> void {
        dfn[u] = ++ti;
        dep[u] = dep[p] + 1;
        siz[u] = 1;
        fa[u][0] = p;
        for (int i = 1; i <= 20; i++) {
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        }
        for (int v : adj[u]) {
            if (v == p) continue;
            self(self, v, u);
            siz[u] += siz[v];
        }
        out[u] = ti;
    };
    dfs_lca(dfs_lca, 1, 0);
    
    auto get_lca = [&](int u, int v) -> int {
        if (dep[u] < dep[v]) swap(u, v);
        for (int i = 20; i >= 0; i--) {
            if (dep[fa[u][i]] >= dep[v]) {
                u = fa[u][i];
            }
        }
        if (u == v) return u;
        for (int i = 20; i >= 0; i--) {
            if (fa[u][i] != fa[v][i]) {
                u = fa[u][i];
                v = fa[v][i];
            }
        }
        return fa[u][0];
    };
    vector<vii> vtree(n+1);
    vector<pii> belong(n+1, {inf, inf}); // {dist, id}
    vector<int> rem(n+1);
    vector<int> ans(n+1);
    int q; cin >> q;
    while(q--){
        int m; cin >> m;
        vector<int> h(m);
        vector<int> xs;
        for(int i = 0; i < m; i++){
            cin >> h[i];
            xs.pb(h[i]);
            belong[h[i]] = {0, h[i]};
        }
        xs.pb(1);

        sort(xs.begin(), xs.end(), [&](int a, int b) {
            return dfn[a] < dfn[b];
        });
        int sz = xs.size();
        for(int i = 0; i < sz - 1; i++){
            xs.pb(get_lca(xs[i], xs[i + 1]));
        }
        sort(xs.begin(), xs.end(), [&](int a, int b) {
            return dfn[a] < dfn[b];
        });
        xs.erase(unique(xs.begin(), xs.end()), xs.end());

        for(int i = 1; i < xs.size(); i++){
            int lca = get_lca(xs[i - 1], xs[i]);
            vtree[lca].pb(xs[i]);
        }

        auto dfs1 = [&](auto& self, int u) -> void {
            for(int v : vtree[u]) {
                self(self, v);
                int d = belong[v].fi + (dep[v] - dep[u]);
                belong[u] = min(belong[u], {d, belong[v].se});
            }
        };
        dfs1(dfs1, 1);

        auto dfs2 = [&](auto& self, int u) -> void {
            for(int v : vtree[u]) {
                int d = belong[u].fi + (dep[v] - dep[u]);
                belong[v] = min(belong[v], {d, belong[u].se});
                self(self, v);
            }
        };
        dfs2(dfs2, 1);

        auto dfs = [&](auto& self, int u) -> void {
            rem[u] = siz[u];
            for(int v : vtree[u]){
                self(self, v);
                int w = v;
                for(int i = 20; i >= 0; i--){
                    if(dep[fa[w][i]] > dep[u]) {
                        w = fa[w][i];
                    }
                }
                rem[u] -= siz[w];
                if(belong[u].se == belong[v].se){
                    ans[belong[u].se] += siz[w] - siz[v];
                }else{
                    int len = dep[v] - dep[u];
                    int du = belong[u].fi, dv = belong[v].fi;
                    int k = (du + len - dv) / 2;
                    if((du + len - dv) % 2 == 0 && belong[v].se > belong[u].se) k--;
                    k = max(0LL, min(k, len - 1));
                    int mid = v;
                    for(int i = 20; i >= 0; i--){
                        if((k >> i) & 1){
                            mid = fa[mid][i];
                        }
                    }
                    ans[belong[u].se] += siz[w] - siz[mid];
                    ans[belong[v].se] += siz[mid] - siz[v];
                }
            }
            ans[belong[u].se] += rem[u];
        };
        dfs(dfs, 1);

        for(int i = 0; i < m; i++) {
            cout << ans[h[i]] << " ";
        }
        cout << endl;
        for(int u : xs){
            vtree[u].clear();
            belong[u] = {inf, inf};
            rem[u] = 0;
            ans[u] = 0;
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