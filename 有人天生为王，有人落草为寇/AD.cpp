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
    e-BCC 建完树后, 答案就是树上直径
    跑两边bfs就行
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
    // 建立缩点树
    vector<vii> tree(ebcc_cnt+1); 
    for (int i = 1; i <= m; i++) {
        auto [u, v] = e[i];
        if (ebcc_id[u] != ebcc_id[v]) {
            tree[ebcc_id[u]].pb(ebcc_id[v]);
            tree[ebcc_id[v]].pb(ebcc_id[u]);
        }
    }
    
    if(ebcc_cnt <= 1){
        cout << 0 << endl;
        return;
    }
    auto bfs = [&](int s) -> pii {
        vii dist(ebcc_cnt+1, -1);
        queue<int> q;
        dist[s] = 0;
        q.push(s);
        int far_node = s;
        int mx_dist = 0;
        while(q.size()){
            int u = q.front();
            q.pop();
            if (dist[u] > mx_dist) {
                mx_dist = dist[u];
                far_node = u;
            }
            for (int v : tree[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        return {far_node, mx_dist};
    };
    auto [c1, _] = bfs(1);
    auto [c2, ans] = bfs(c1);
    cout << ans << endl;
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