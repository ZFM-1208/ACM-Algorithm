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
    vector<vii> adj(n + 1);
    for(int i = 1; i < n; i++){
        int u, v; cin >> u >> v;
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
    vector<vii> vtree(n+1);
    vii vis(n+1), cnt(n+1), mn(n+1), mx(n+1);
    // cnt[u]：以 u 为根的虚树子树内包含的关键点数量
    // mn[u]：u 到其虚树子树内某个关键点的最小距离
    // mx[u]：u 到其虚树子树内某个关键点的最大距离
    int q; cin >> q;
    while(q--){
        int k; cin >> k;
        vector<int> xs;
        for(int i = 1; i <= k; i++){
            int x; cin >> x;
            vis[x] = 1;
            xs.push_back(x);
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

        stack<int> st;
        for(int u: xs){
            while(st.size() && out[st.top()] < dfn[u]){
                st.pop();
            }
            if(st.size()) vtree[st.top()].push_back(u);
            st.push(u);
        }
        for(int u : xs){
            if(vis[u]){
                cnt[u] = 1;
                mn[u] = 0;
                mx[u] = 0;
            }else{
                cnt[u] = 0;
                mn[u] = inf;
                mx[u] = -inf;
            }
        }
        int sum = 0;
        int mnn = inf;
        int mxx = -inf;
        auto dfs = [&](auto& self, int u) -> void {
            for(int v : vtree[u]) {
                self(self, v);
                int w = dep[v] - dep[u];
                sum += w * cnt[v] * (k - cnt[v]);
                cnt[u] += cnt[v];
                mnn = min(mnn, mn[u] + mn[v] + w);
                mxx = max(mxx, mx[u] + mx[v] + w);
                mn[u] = min(mn[u], mn[v] + w);
                mx[u] = max(mx[u], mx[v] + w);
            }
        };

        dfs(dfs, xs[0]);
        cout << sum << " " << mnn << " " << mxx << endl;
        for(int u : xs){
            vtree[u].clear();
            vis[u] = 0;
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