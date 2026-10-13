#include <bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for (int i = l; i <= r; i++)
#define vii vector<int>
#define int long long
#define pb push_back
#define endl '\n'

void solve() {
    int n, m;cin >> n >> m;
    vector<vii> adj(n + 1);
    rep(i, 1, m) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v); // 有向边
    }

    // ==================== Tarjan SCC 核心 ====================
    vii dfn(n + 1, 0), low(n + 1, 0);
    vii scc_id(n + 1, 0);       // 每个点所属的 SCC 编号 (1 ~ scc_cnt)
    vii scc_sz;                 // 记录每个 SCC 包含的顶点数
    vector<bool> in_st(n + 1, false);
    stack<int> st;
    int dfn_cnt = 0, scc_cnt = 0;

    auto tarjan = [&](auto& self, int u) -> void {
        dfn[u] = low[u] = ++dfn_cnt;
        st.push(u);
        in_st[u] = true;

        for (int v : adj[u]) {
            if (!dfn[v]) {
                self(self, v);
                low[u] = min(low[u], low[v]);
            } else if (in_st[v]) {
                // 只有在栈中的祖先/同连通块节点才能用来更新 low
                low[u] = min(low[u], dfn[v]);
            }
        }

        // 找到强连通分量的根
        if (low[u] == dfn[u]) {
            scc_cnt++;
            int cur_sz = 0;
            while (true) {
                int x = st.top();
                st.pop();
                in_st[x] = false;
                scc_id[x] = scc_cnt;
                cur_sz++;
                if (x == u) break;
            }
            scc_sz.pb(cur_sz); // 记录当前分量大小 (0-indexed 对应 id - 1)
        }
    };

    // 外层遍历所有点（处理非连通有向图）
    rep(i, 1, n) {
        if (!dfn[i]) {
            tarjan(tarjan, i);
        }
    }

    // ==================== 缩点建 DAG ====================
    vector<vii> dag(scc_cnt + 1);
    vii in_deg(scc_cnt + 1, 0);

    rep(u, 1, n) {
        for (int v : adj[u]) {
            if (scc_id[u] != scc_id[v]) {
                dag[scc_id[u]].pb(scc_id[v]);
            }
        }
    }

    // 邻接表排序去重，避免重复边干扰入度与 DP
    rep(i, 1, scc_cnt) {
        sort(dag[i].begin(), dag[i].end());
        dag[i].erase(unique(dag[i].begin(), dag[i].end()), dag[i].end());
        for (int v : dag[i]) {
            in_deg[v]++;
        }
    }

    // 拓扑序 DP 示例：直接利用 scc_cnt 逆序遍历
    // for (int u = scc_cnt; u >= 1; u--) {
    //     for (int v : dag[u]) {
    //         dp[v] = max(dp[v], dp[u] + val[v]);
    //     }
    // }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}