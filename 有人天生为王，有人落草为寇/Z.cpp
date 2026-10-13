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
struct edge {
    int to;
    int id; 
};
void solve(){
    int n, m; cin >> n >> m;
    vector<vector<edge>> adj(n + 1);
    vector<pii> e(m + 1);
    for(int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb({v, i});
        adj[v].pb({u, i});
        e[i] = {u, v};
    }

    vii dfn(n + 1, 0), low(n + 1, 0);
    vii ebcc_id(n + 1, 0);      // 每个点所属的 e-BCC 编号
    vector<bool> is_bridge(m + 1, false); // 标记每条边是否为桥
    int dfn_cnt = 0, ebcc_cnt = 0;
    stack<int> st;
    vector<vii> ebcc_nodes; // 收集各个边双分量包含的节点
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
            vii cur_nodes;
            while (true) {
                int x = st.top();
                st.pop();
                ebcc_id[x] = ebcc_cnt;
                cur_nodes.pb(x);
                if (x == u) break;
            }
            ebcc_nodes.pb(cur_nodes); 
        }
    };

    rep(i, 1, n){
        if(!dfn[i]) tarjan(tarjan, i, 0);
    }
    cout << ebcc_nodes.size() << endl;
    for(auto cur: ebcc_nodes){
        cout << cur.size() << " ";
        for(int x: cur){
            cout << x << " ";
        }
        cout << endl;
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