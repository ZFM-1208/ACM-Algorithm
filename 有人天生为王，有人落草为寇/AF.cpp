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

struct edge {
    int to;
    int id; 
};
// 没有自环，没有重边，图连通
void solve() {
    int n, m; cin >> n >> m;
    vector<vector<edge>> adj(n + 1);
    vector<array<int,3>> e(m + 1);
    for(int i = 1; i <= m; i++) {
        int u, v, z;
        cin >> u >> v >> z;
        adj[u].pb({v, i});
        adj[v].pb({u, i});
        e[i] = {u, v, z};
    }
    int sn, en;
    cin >> sn >> en;

    vii dfn(n + 1, 0), low(n + 1, 0);
    vii ebcc_id(n + 1, 0);
    vector<bool> is_bridge(m + 1, false);
    int dfn_cnt = 0, ebcc_cnt = 0;
    stack<int> st;

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

        if (low[u] == dfn[u]) {
            ebcc_cnt++;
            while (true) {
                int x = st.top();
                st.pop();
                ebcc_id[x] = ebcc_cnt;
                if (x == u) break;
            }
        }
    };

    rep(i, 1, n) {
        if (!dfn[i]) tarjan(tarjan, i, 0);
    }

    vector<int> vis(ebcc_cnt + 1);
    // {目标分量编号, 该桥是否带神器}
    vector<vector<pii>> tree(ebcc_cnt + 1);
    for(int i = 1; i <= m; i++) {
        auto [u, v, z] = e[i];
        int cu = ebcc_id[u];
        int cv = ebcc_id[v];
        if(cu == cv){
            if(z == 1){
                vis[cu] = 1;
            }
        }else{
            tree[cu].pb({cv, z});
            tree[cv].pb({cu, z});
        }
    }

    int cs = ebcc_id[sn];
    int ce = ebcc_id[en];
    bool ok = false;
    auto dfs = [&](auto& self, int u, int p, bool got) -> void {
        got |= vis[u];
        if(u == ce){
            if (got) ok = true;
            return;
        }
        for(auto [v, z] : tree[u]){
            if (v == p) continue;
            self(self, v, u, got | (z == 1));
        }
    };
    dfs(dfs, cs, 0, false);
    if (ok) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}