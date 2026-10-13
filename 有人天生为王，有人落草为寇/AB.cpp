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
    "任意两片牧场之间至少有两条互不共用任何路径的不同路线"
    -> 即使它们可能经过相同的中间牧场
    边双 e-BCC

    "注意，可能已经存在多条路径连接同一对牧场"
    -> 可能有重边

    题目的本质：
    最少添加多少条无向边，使得整张图变成一个巨大的边双连通图
    (没有一座桥(割边))
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
    vii du(ebcc_cnt+1);
    for(int i = 1; i <= m; i++){
        auto [u,v] = e[i];
        if (ebcc_id[u] != ebcc_id[v]) {
            du[ebcc_id[u]]++;
            du[ebcc_id[v]]++;
        }
    }
    int cnt = 0;
    for(int i = 1; i <= ebcc_cnt; i++){
        if(du[i] == 1) cnt++;
    }
    cout << (cnt + 1) / 2 << endl;
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