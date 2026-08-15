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
struct node {
    int round; 
    int id;    
    int dist;  
    int u;     
    bool operator>(const node& other) const {
        if (round != other.round) return round > other.round;
        return id > other.id;
    }
};
void solve(){
    int n; cin >> n;
    vector<vii> adj(n+1);
    for(int i = 1; i < n; i++){
        int u,v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    vector<int> dep(n + 1), dfn(n + 1), out(n + 1);
    vector<vector<int>> fa(n + 1, vector<int>(25));
    int ti = 0;
    auto dfs_lca = [&](auto& self, int u, int p) -> void {
        dfn[u] = ++ti;
        dep[u] = dep[p] + 1;
        fa[u][0] = p;
        for (int i = 1; i <= 20; i++) {
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        }
        for (int v : adj[u]) {
            if (v == p) continue;
            self(self, v, u);
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
    
    vector<vector<pii>> vtree(n+1);
    vii vis(n+1), ans(n+1);
    int q; cin >> q;
    while(q--){
        int k,m; cin >> k >> m;
        vector<pii> a(k + 1); // {起点, 速度}
        vector<int> xs;            

        for(int i = 1; i <= k; i++){
            cin >> a[i].fi >> a[i].se;
            xs.pb(a[i].fi);
        }
        vector<int> city(m);
        for(int i = 0; i < m; i++){
            cin >> city[i];
            xs.pb(city[i]);
        }

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

        for(int i = 1; i < xs.size(); i++){
            int p = get_lca(xs[i - 1], xs[i]);
            int w = dep[xs[i]] - dep[p];
            vtree[p].pb({xs[i], w});
            vtree[xs[i]].pb({p, w});
        }
        priority_queue<node, vector<node>, greater<node>> pq;
        for(int i = 1; i <= k; i++){
            pq.push({0, i, 0, a[i].fi});
        }

        while(!pq.empty()){
            auto [cur_r, id, d, u] = pq.top();
            pq.pop();
            if (vis[u]) continue;
            vis[u] = 1;
            ans[u] = id;
            for(auto [v, w] : vtree[u]) {
                if (vis[v]) continue;
                int nd = d + w;
                int nr = (nd + a[id].se - 1) / a[id].se;
                pq.push({nr, id, nd, v});
            }
        }
        for(int i = 0; i < m; i++){
            cout << ans[city[i]] << " ";
        }
        cout << endl;
        for(int u : xs) {
            vtree[u].clear();
            vis[u] = 0;
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