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
    int n,m,q; cin >> n >> m >> q;
    vector<vii> adj(n+1);
    for(int i = 1; i <= m; i++){
        int u,v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    // 1. Tarjan 求点双，建立圆方树
    // 圆点编号: 1 ~ n；方点编号: n + 1 ~ 2n
    int dfn_cnt = 0, bcc_cnt = 0;
    vii dfn(n + 1, 0), low(n + 1, 0);
    stack<int> st;

    // 圆方树邻接表，开 2 * n + 5 保证不越界
    vector<vii> tree(2 * n + 5);

    auto tarjan = [&](auto& self, int u, int fa) -> void {
        dfn[u] = low[u] = ++dfn_cnt;
        st.push(u);

        // 孤立点特判（没有连边时直接退栈）
        if (adj[u].empty()) {
            st.pop();
            return;
        }

        for (int v : adj[u]) {
            if (v == fa) continue; // 忽略反向树边

            if (!dfn[v]) {
                self(self, v, u);
                low[u] = min(low[u], low[v]);

                // 找到割点或以 u 为根的点双连通分量
                if (low[v] >= dfn[u]) {
                    bcc_cnt++;
                    int square = n + bcc_cnt; // 新建方点

                    // 割点 u 连向方点
                    tree[u].pb(square);
                    tree[square].pb(u);

                    // 弹出该点双内的其余圆点并与方点连边
                    while (true) {
                        int x = st.top();
                        st.pop();
                        tree[x].pb(square);
                        tree[square].pb(x);
                        if (x == v) break;
                    }
                }
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
    };

    // 外层循环：支持非连通图 / 森林
    rep(i, 1, n) {
        if (!dfn[i]) {
            tarjan(tarjan, i, 0);
        }
    }

    // 倍增处理LCA
    int tot = n + bcc_cnt;
    vector<int> dep(tot+1);
    vector<vii> up(tot+1, vii(21,0));
    auto dfs = [&](auto&self, int u, int p) -> void {
        dep[u] = dep[p] + 1;
        up[u][0] = p;
        for(int j = 1; j <= 20; j++){
            up[u][j] = up[up[u][j-1]][j-1];
        }
        for(int v: tree[u]){
            if(v != p) self(self, v, u);
        }
    };
    dfs(dfs,1,0);

    auto get_lca = [&](int u, int v) -> int {
        if (dep[u] < dep[v]) swap(u, v);
        for (int j = 20; j >= 0; j--) {
            if (dep[u] - (1LL << j) >= dep[v]) {
                u = up[u][j];
            }
        }
        if (u == v) return u;
        for (int j = 20; j >= 0; j--) {
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }
        return up[u][0];
    };

    while(q--){
        int s,t; cin >> s >> t;
        if(s == t){
            cout << 0 << endl;
            continue;
        }
        int lca = get_lca(s,t);
        int dist = dep[s] + dep[t] - 2 * dep[lca];
        int ans = dist / 2 - 1;
        cout << ans << endl;
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