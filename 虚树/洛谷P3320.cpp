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
    int n,m; cin >> n >> m;
    vector<vector<pii>> adj(n+1);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
    vector<int> dep(n+1), dfn(n+1), dis(n+1);
    vector<vii> fa(n+1, vii(21));
    int ti = 0;
    auto dfs_lca = [&](auto& self, int u, int p, int d) -> void {
        dfn[u] = ++ti;
        dep[u] = dep[p] + 1;
        dis[u] = d;
        fa[u][0] = p;
        for (int i = 1; i <= 20; i++) {
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        }
        for (auto [v, w] : adj[u]) {
            if (v == p) continue;
            self(self, v, u, d + w);
        }
    };
    dfs_lca(dfs_lca, 1, 0, 0);

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
    int ans = 0;
    set<pii> st; // set 维护当前有宝物的点集 {dfn[u], u}
    vector<int> vis(n+1);
    auto get_dist = [&](int u, int v) -> int {
        int p = get_lca(u, v);
        return dis[u] + dis[v] - 2 * dis[p];
    };
    auto get_l = [&](auto it) -> int {
        if (it == st.begin()) it = st.end();
        --it;
        return it->se;
    };

    auto get_r = [&](auto it) -> int {
        ++it;
        if (it == st.end()) it = st.begin();
        return it->se;
    };
    while(m--){
        int x; cin >> x;
        if(vis[x] == 0){ // 插入 x
            if(st.empty()) {
                st.insert({dfn[x], x});
                vis[x] = 1;
            }
            else if(st.size() == 1){
                ans += 2 * get_dist(x, st.begin() -> second);
                st.insert({dfn[x], x});
                vis[x] = 1;
            }else{
                auto it = st.lower_bound({dfn[x], x});
                int r = (it == st.end() ? st.begin()->second : it->second);
                int l = get_l(it == st.end() ? st.begin() : it);
                ans -= get_dist(l, r);
                ans += get_dist(l, x) + get_dist(x, r);
                st.insert({dfn[x], x});
                vis[x] = 1;
            }
        }else{ // 删除 x
            if(st.size() <= 2){
                ans = 0;
                st.erase({dfn[x], x});
                vis[x] = 0;
            }else{
                auto it = st.find({dfn[x], x});
                int l = get_l(it);
                int r = get_r(it);
                ans -= get_dist(l, x) + get_dist(x, r);
                ans += get_dist(l, r);
                st.erase(it);   
                vis[x] = 0;         
            }
        }
        cout << ans << endl;
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