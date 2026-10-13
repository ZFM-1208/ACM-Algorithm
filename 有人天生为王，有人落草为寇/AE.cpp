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
    ans = min(ebcc_sz[c]);
    反向构造即可
*/
struct Edge {
    int to;
    int id; 
};

void solve(){
    int n,m; cin >> n >> m;
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

    vii ebcc_sz(ebcc_cnt + 1, 0);
    rep(i, 1, n) {
        ebcc_sz[ebcc_id[i]]++;
    }
    int max_sz = 0;
    int best_bcc = 1;
    rep(c, 1, ebcc_cnt) {
        if (ebcc_sz[c] > max_sz) {
            max_sz = ebcc_sz[c];
            best_bcc = c;
        }
    }
    // 在最大边双中挑选任意一个顶点作为全图 DFS 的终极根节点 rt
    int rt = 1;
    rep(i, 1, n) {
        if (ebcc_id[i] == best_bcc) {
            rt = i;
            break;
        }
    }

    vector<pii> ans(m + 1);
    vii vis_node(n + 1);
    vii vis_edge(m + 1);
    auto dfs = [&](auto& self, int u) -> void {
        vis_node[u] = 1;
        for (auto [v, eid] : adj[u]) {
            if(vis_edge[eid]) continue;
            vis_edge[eid] = 1;
            ans[eid] = {v, u};
            if(!vis_node[v]){
                self(self, v);
            }
        }
    };
    dfs(dfs, rt);
    cout << max_sz << endl;
    rep(i, 1, m) {
        cout << ans[i].fi << " " << ans[i].se << endl;
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