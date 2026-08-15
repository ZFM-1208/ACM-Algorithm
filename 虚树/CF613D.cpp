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
        int u,v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vii dep(n+1), dfn(n+1), out(n+1);
    vector<vii> fa(n+1, vii(25)); 
    int ti = 0;
    auto dfs_lca = [&](auto& self, int u, int p) -> void {
        dfn[u] = ++ti; 
        dep[u] = dep[p] + 1;
        fa[u][0] = p;
        for(int i = 1; i <= 20; i++){
            fa[u][i] = fa[fa[u][i-1]][i-1];
        }
        for(int v: adj[u]){
            if(v == p) continue;
            self(self, v, u);
        }
        out[u] = ti; 
    };
    dfs_lca(dfs_lca, 1, 0);
    auto get_lca = [&](int u, int v) -> int {
        if(dep[u] < dep[v])swap(u, v);
        for(int i = 20; i >= 0; i--){
            if(dep[fa[u][i]] >= dep[v]){
                u = fa[u][i];
            }
        }
        if(u == v) return u;
        for(int i = 20; i >= 0; i--){
            if (fa[u][i] != fa[v][i]){
                u = fa[u][i];
                v = fa[v][i];
            }
        }
        return fa[u][0];
    };

    int q; cin >> q;
    vector<int> vis(n+1);
    vector<vii> vtree(n+1);
    while(q--){
        int k; cin >> k;
        
        vector<int> xs;
        for(int i = 1; i <= k; i++){
            int x; cin >> x;
            vis[x] = 1;
            xs.push_back(x);
        }
        bool ok = 0;
        for(int u : xs){
            if(vis[fa[u][0]]){
                cout << -1 << endl;
                ok = 1;
                break;
            }
        }
        if(ok) {
            for (int u : xs) vis[u] = 0;
            continue; 
        }
        sort(xs.begin(), xs.end(),[&](auto x, auto y){
            return dfn[x] < dfn[y];
        });
        int sz = xs.size();
        for(int i = 0; i < sz - 1; i++){
            int lca = get_lca(xs[i], xs[i+1]);
            xs.push_back(lca);
        }
        sort(xs.begin(), xs.end(),[&](auto x, auto y){
            return dfn[x] < dfn[y];
        });
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        
        for(int i = 1; i < xs.size(); i++){
            int fa = get_lca(xs[i], xs[i-1]);
            vtree[fa].push_back(xs[i]);
        }
        // stack<int> st;
        // for(int u: xs){
        //     while(st.size() && out[st.top()] < dfn[u]){
        //         st.pop();
        //     }
        //     if(st.size()) vtree[st.top()].push_back(u);
        //     st.push(u);
        // }
        int ans = 0;
        // dfs[u]: 表示以 u 为根的子树内，是否有未被阻断的重要城市正在向上连通(1/0)
        // cnt = u的亲孩子节点子树中向上的重要城市数量
        auto dfs = [&](auto& self, int u) -> int {
            int cnt = 0;
            for(int v : vtree[u]){
                cnt += self(self, v);
            }
            if(vis[u] == 1){
                ans += cnt;
                return 1;
            }else if(cnt >= 2){
                ans++;
                return 0;
            }else if(cnt == 1){
                return 1;
            }else {
                return 0;
            }
        };

        dfs(dfs, xs[0]);
        
        cout << ans << endl;
        for (int u : xs) {
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