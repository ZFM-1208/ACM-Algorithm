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
/*
    e-BCC 树上动态维护
    建树, 最后有 ebcc_cnt - 1 条树边(桥)
    我们在u, v加边 (u,v属于不同的边双), 会消除缩点树上 $cu$ 到 $cv$ 路径上的所有树边
    直接找lca, 然后去消除, 时间复杂度最坏是O(q*n)
    为了高效消桥 -- > 树上并查集DSU

*/
struct Edge {
    int to;
    int id; 
};
int case_cnt = 0;

void solve(int n, int m){
    vector<vector<Edge>> adj(n + 1);
    vector<pii> e(m + 1);
    for(int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb({v, i});
        adj[v].pb({u, i});
        e[i] = {u, v};
    }
    vii dfn(n + 1, 0), low(n + 1, 0);
    vii ebcc_id(n + 1, 0);
    vector<bool> is_bridge(m + 1, false);
    int dfn_cnt = 0, ebcc_cnt = 0;
    stack<int> st;
    // vector<vii> ebcc_nodes; 
    auto tarjan = [&](auto& self, int u, int in_edge_id) -> void {
        dfn[u] = low[u] = ++dfn_cnt;
        st.push(u);
        for (auto [v, eid] : adj[u]) {
            if (eid == in_edge_id) continue;
            if (!dfn[v]) {
                self(self, v, eid);
                low[u] = min(low[u], low[v]);
                if (low[v] > dfn[u]) {
                    is_bridge[eid] = true;
                }
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }

        if(low[u] == dfn[u]){
            ebcc_cnt++;
            vii cur_nodes;
            while (true) {
                int x = st.top();
                st.pop();
                ebcc_id[x] = ebcc_cnt;
                // cur_nodes.pb(x);
                if (x == u) break;
            }
            // ebcc_nodes.pb(cur_nodes); 
        }
    };

    rep(i, 1, n) {
        if(!dfn[i])  tarjan(tarjan, i, 0);
    }
    // 建立缩点树
    vector<vii> tree(ebcc_cnt+1); 
    for (int i = 1; i <= m; i++) {
        auto [u, v] = e[i];
        if (ebcc_id[u] != ebcc_id[v]) {
            tree[ebcc_id[u]].pb(ebcc_id[v]);
            tree[ebcc_id[v]].pb(ebcc_id[u]);
        }
    }
    vii fa(ebcc_cnt + 1, 0), dep(ebcc_cnt + 1, 0);
    auto dfs_tree = [&](auto& self, int u, int p, int d) -> void {
        fa[u] = p;
        dep[u] = d;
        for (int v : tree[u]) {
            if (v != p) {
                self(self, v, u, d + 1);
            }
        }
    };
    dfs_tree(dfs_tree, 1, 0, 1);
    
    vii p(ebcc_cnt+1);
    iota(p.begin(), p.end(),0);
    auto find = [&](auto& self, int x) -> int {
        return p[x] == x ? x : p[x] = self(self, p[x]);
    };
    int cnt = ebcc_cnt - 1; // 桥个数
    auto merge = [&](int u, int v) -> void {
        u = find(find, u);
        v = find(find, v);
        while (u != v) {
            if (dep[u] < dep[v]) swap(u, v);
            cnt--;
            p[u] = find(find, fa[u]);
            u = p[u];
        }
    };
    cout << "Case " << ++case_cnt << ":" << endl;
    int q; cin >> q;
    while(q--){
        int u,v; cin >> u >> v;
        merge(ebcc_id[u], ebcc_id[v]);
        cout << cnt << endl;
    }
    cout << endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T = 1;
    // cin >> T;
    int n,m; 
    while(cin >> n >> m && (n || m))
        solve(n,m);
    return 0;
}