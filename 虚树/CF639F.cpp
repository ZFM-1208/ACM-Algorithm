#include <bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for (int i = l; i <= r; i++)
#define vii vector<int>
#define pii pair<int, int>
#define pb push_back
#define fi first
#define se second
#define endl '\n'

const int N = 3e5 + 5;

// ==================== 1. 全局原图与 Tarjan 缩点 ====================
struct Edge {
    int to, nxt, id;
};

int head_g[N], edge_cnt = 1;
Edge g[N << 1];

void add_raw_edge(int u, int v, int id) {
    g[++edge_cnt] = {v, head_g[u], id}; head_g[u] = edge_cnt;
    g[++edge_cnt] = {u, head_g[v], id}; head_g[v] = edge_cnt;
}

int dfn[N], low[N], ti = 0;
int ecc_cnt = 0, ecc1[N]; // ecc1[u]: 节点 u 属于原图的哪个边双连通分量
int stk[N], top = 0;

void tarjan_global(int u, int in_edge) {
    dfn[u] = low[u] = ++ti;
    stk[++top] = u;
    for (int e = head_g[u]; e; e = g[e].nxt) {
        if (g[e].id == in_edge) continue; // 不沿反向边回去
        int v = g[e].to;
        if (!dfn[v]) {
            tarjan_global(v, g[e].id);
            low[u] = min(low[u], low[v]);
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
    // 发现边双连通分量的根
    if (low[u] == dfn[u]) {
        ecc_cnt++;
        while (true) {
            int x = stk[top--];
            ecc1[x] = ecc_cnt;
            if (x == u) break;
        }
    }
}

// ==================== 2. 缩点后的森林预处理 ====================
vector<int> tree_adj[N];
int dep[N], tree_dfn[N], tree_id[N], tree_ti = 0;
int fa[N][21];

void dfs_forest(int u, int p, int tid) {
    tree_dfn[u] = ++tree_ti;
    dep[u] = dep[p] + 1;
    fa[u][0] = p;
    tree_id[u] = tid;
    for (int i = 1; i <= 20; i++) {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    }
    for (int v : tree_adj[u]) {
        if (v == p) continue;
        dfs_forest(v, u, tid);
    }
}

int get_lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 20; i >= 0; i--) {
        if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    }
    if (u == v) return u;
    for (int i = 20; i >= 0; i--) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

// ==================== 3. 局部虚图与第二次 Tarjan ====================
vector<pii> vgraph[N]; // 虚图邻接表: {to, edge_id}
int v_dfn[N], v_low[N], v_ti = 0;
int ecc2_cnt = 0, ecc2[N];
int v_stk[N], v_top = 0;

void tarjan_local(int u, int in_edge) {
    v_dfn[u] = v_low[u] = ++v_ti;
    v_stk[++v_top] = u;
    for (auto [v, id] : vgraph[u]) {
        if (id == in_edge) continue;
        if (!v_dfn[v]) {
            tarjan_local(v, id);
            v_low[u] = min(v_low[u], v_low[v]);
        } else {
            v_low[u] = min(v_low[u], v_dfn[v]);
        }
    }
    if (v_low[u] == v_dfn[u]) {
        ecc2_cnt++;
        while (true) {
            int x = v_stk[v_top--];
            ecc2[x] = ecc2_cnt;
            if (x == u) break;
        }
    }
}

void solve() {
    int n, m, q; cin >> n >> m >> q;
    for(int i = 1; i <= m; i++){
        int u, v; cin >> u >> v;
        add_raw_edge(u, v, i);
    }
    // 第一步：原图 Tarjan 缩点
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan_global(i, 0);
    }

    // 第二步：建出缩点后的森林（桥作为树边）
    for (int u = 1; u <= n; u++) {
        for (int e = head_g[u]; e; e = g[e].nxt) {
            int v = g[e].to;
            if (ecc1[u] != ecc1[v]) {
                tree_adj[ecc1[u]].pb(ecc1[v]);
            }
        }
    }
    // 对缩点森林做 DFS 预处理 LCA
    for (int i = 1; i <= ecc_cnt; i++) {
        if (!tree_dfn[i]) dfs_forest(i, 0, i);
    }

    int R = 0; // 强制在线偏移量
    auto rotate = [&](int element) -> int {
        element = (element + R) % n;
        if (element == 0) element = n;
        return element;
    };

    // 第三步：处理 Q 次询问
    for (int qid = 1; qid <= q; qid++) {
        int ni, mi;
        cin >> ni >> mi;

        vector<int> q_nodes(ni);
        vector<int> xs; // 虚树关键点（映射到 ecc1）

        for (int i = 0; i < ni; i++) {
            cin >> q_nodes[i];
            q_nodes[i] = ecc1[rotate(q_nodes[i])];
            xs.pb(q_nodes[i]);
        }

        vector<pii> tmp_edges(mi);
        for (int i = 0; i < mi; i++) {
            int u, v;
            cin >> u >> v;
            u = ecc1[rotate(u)];
            v = ecc1[rotate(v)];
            tmp_edges[i] = {u, v};
            xs.pb(u);
            xs.pb(v);
        }

        if (ni == 1) {
            cout << "YES" << endl;
            R = (R + qid) % n;
            continue;
        }

        // 森林虚树排序建树
        sort(xs.begin(), xs.end(), [&](int a, int b) {
            if (tree_id[a] != tree_id[b]) return tree_id[a] < tree_id[b];
            return tree_dfn[a] < tree_dfn[b];
        });
        xs.erase(unique(xs.begin(), xs.end()), xs.end());

        int sz = xs.size();
        for (int i = 0; i < sz - 1; i++) {
            if (tree_id[xs[i]] == tree_id[xs[i + 1]]) {
                xs.pb(get_lca(xs[i], xs[i + 1]));
            }
        }
        sort(xs.begin(), xs.end(), [&](int a, int b) {
            if (tree_id[a] != tree_id[b]) return tree_id[a] < tree_id[b];
            return tree_dfn[a] < tree_dfn[b];
        });
        xs.erase(unique(xs.begin(), xs.end()), xs.end());

        // 建立虚图边
        int local_edge_id = 0;
        auto add_local_edge = [&](int u, int v) {
            if (u == v) return;
            local_edge_id++;
            vgraph[u].pb({v, local_edge_id});
            vgraph[v].pb({u, local_edge_id});
        };

        for (int i = 1; i < (int)xs.size(); i++) {
            if (tree_id[xs[i - 1]] == tree_id[xs[i]]) {
                int p = get_lca(xs[i - 1], xs[i]);
                add_local_edge(p, xs[i]);
            }
        }
        // 加入询问给定的临时边
        for (auto [u, v] : tmp_edges) {
            add_local_edge(u, v);
        }

        // 第四步：在虚图上跑第二次局部 Tarjan
        v_ti = 0;
        ecc2_cnt = 0;
        for (int u : xs) {
            if (!v_dfn[u]) tarjan_local(u, 0);
        }

        // 第五步：验证所有查询点是否在同一个边双连通分量中
        bool ok = true;
        int target_ecc = ecc2[q_nodes[0]];
        for (int i = 1; i < ni; i++) {
            if (ecc2[q_nodes[i]] != target_ecc) {
                ok = false;
                break;
            }
        }

        if (ok) {
            cout << "YES" << endl;
            R = (R + qid) % n;
        } else {
            cout << "NO" << endl;
        }

        // 第六步：O(ni + mi) 清空现场
        for (int u : xs) {
            vgraph[u].clear();
            v_dfn[u] = 0;
            v_low[u] = 0;
            ecc2[u] = 0;
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}