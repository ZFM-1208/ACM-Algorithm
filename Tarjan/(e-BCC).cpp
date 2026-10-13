#include <bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for (int i = l; i <= r; i++)
#define vii vector<int>
#define int long long
#define pb push_back
#define endl '\n'

struct Edge {
    int to;
    int id; // 边的唯一编号 (1 ~ m)
};

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    vector<vector<Edge>> adj(n + 1);
    vector<pair<int, int>> edges(m + 1);

    rep(i, 1, m) {
        int u, v;
        cin >> u >> v;
        adj[u].pb({v, i});
        adj[v].pb({u, i});
        edges[i] = {u, v};
    }

    // ==================== e-BCC Tarjan 核心 ====================
    vii dfn(n + 1, 0), low(n + 1, 0);
    vii ebcc_id(n + 1, 0);      // 每个点所属的 e-BCC 编号
    vector<bool> is_bridge(m + 1, false); // 标记每条边是否为桥
    int dfn_cnt = 0, ebcc_cnt = 0;
    stack<int> st;
    vector<vii> ebcc_nodes; // 收集各个边双分量包含的节点
    auto tarjan = [&](auto& self, int u, int in_edge_id) -> void {
        dfn[u] = low[u] = ++dfn_cnt;
        st.push(u);

        for (auto& edge : adj[u]) {
            int v = edge.to;
            int eid = edge.id;

            if (eid == in_edge_id) continue; // 仅跳过当前走来的同一条边，不惧重边

            if (!dfn[v]) {
                self(self, v, eid);
                low[u] = min(low[u], low[v]);

                // 1. 判定桥：子节点无法回到 u 或更浅祖先
                if (low[v] > dfn[u]) {
                    is_bridge[eid] = true;
                }
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }

        // 2. 判定边双分量根：与 SCC 弹栈逻辑完全一致
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

    // 外层循环支持非连通图 / 森林
    rep(i, 1, n) {
        if (!dfn[i]) {
            tarjan(tarjan, i, 0);
        }
    }

    // ==================== 缩点建树 ====================
    // 边双缩点后，整张图直接缩成一棵树（或森林）
    // 缩点后树上的边，恰好就是原图的所有“桥”！
    vector<vii> tree(ebcc_cnt + 1);
    rep(i, 1, m) {
        int u = edges[i].first;
        int v = edges[i].second;
        if (ebcc_id[u] != ebcc_id[v]) {
            tree[ebcc_id[u]].pb(ebcc_id[v]);
            tree[ebcc_id[v]].pb(ebcc_id[u]);
        }
    }

    // 输出示例
    cout << "边双总数: " << ebcc_cnt << endl;
    rep(i, 1, n) {
        cout << "点 " << i << " 属于边双 " << ebcc_id[i] << endl;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}