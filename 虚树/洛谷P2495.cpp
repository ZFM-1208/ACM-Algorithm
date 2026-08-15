#include <bits/stdc++.h>
using namespace std;
#define rep(i, l, r) for (int i = l; i <= r; i++)
#define vii vector<int>
#define pii pair<int, int>
#define int long long
#define pb push_back
#define fi first
#define se second
#define endl '\n'
const int inf = 1e18 + 5;

void solve() {
    int n; cin >> n;
    vector<vector<pii>> adj(n + 1);
    for(int i = 1; i < n; i++){
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
    vector<int> dep(n + 1), dfn(n + 1), mn(n + 1, inf);
    vector<vector<int>> fa(n + 1, vector<int>(21));
    int ti = 0;
    auto dfs_lca = [&](auto& self, int u, int p, int x) -> void {
        dfn[u] = ++ti;
        dep[u] = dep[p] + 1;
        fa[u][0] = p;
        mn[u] = x;
        for(int i = 1; i <= 20; i++){
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        }
        for(auto [v, w] : adj[u]){
            if (v == p) continue;
            self(self, v, u, min(x, w));
        }
    };
    dfs_lca(dfs_lca, 1, 0, inf);

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

    vector<vii> vtree(n + 1);
    vector<int> vis(n + 1);
    int m; cin >> m;
    while (m--) {
        int k; cin >> k;
        vector<int> xs;
        for(int i = 1; i <= k; i++) {
            int x; cin >> x;
            vis[x] = 1;
            xs.pb(x);
        }
        xs.pb(1);

        sort(xs.begin(), xs.end(), [&](int a, int b) {
            return dfn[a] < dfn[b];
        });
        int sz = xs.size();
        for (int i = 0; i < sz - 1; i++) {
            xs.pb(get_lca(xs[i], xs[i + 1]));
        }
        sort(xs.begin(), xs.end(), [&](int a, int b) {
            return dfn[a] < dfn[b];
        });
        xs.erase(unique(xs.begin(), xs.end()), xs.end());

        for (int i = 1; i < (int)xs.size(); i++) {
            int p = get_lca(xs[i - 1], xs[i]);
            vtree[p].pb(xs[i]);
        }

        auto dfs_dp = [&](auto& self, int u) -> int {
            int sum = 0;
            for(int v : vtree[u]){
                sum += self(self, v);
            }
            if(vis[u]){
                return mn[u];
            } else {
                return min(mn[u], sum);
            }
        };
        cout << dfs_dp(dfs_dp, 1) << endl;
        for (int u : xs) {
            vtree[u].clear();
            vis[u] = 0;
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}