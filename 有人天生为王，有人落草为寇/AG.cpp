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
    int n,m; cin >> n >> m;
    vii pw2(m+5);
    pw2[0] = 1;
    for(int i = 1; i <= m; i++){
        pw2[i] = (pw2[i - 1] * 2) % mod;
    }
    vector<vector<edge>> adj(n + 1);
    vector<pii> e(m + 1);
    for (int i = 1; i <= m; i++) {
        int u, v; 
        cin >> u >> v;
        adj[u].pb({v, i});
        adj[v].pb({u, i});
        e[i] = {u, v};
    }

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

    vii node_cnt(ebcc_cnt + 1, 0);
    vii edge_cnt(ebcc_cnt + 1, 0);
    rep(i, 1, n) {
        node_cnt[ebcc_id[i]]++;
    }
    vector<vii> tree(ebcc_cnt + 1);
    for (int i = 1; i <= m; i++) {
        auto [u, v] = e[i];
        int cu = ebcc_id[u];
        int cv = ebcc_id[v];
        if (cu == cv) {
            edge_cnt[cu]++; 
        } else {
            tree[cu].pb(cv); 
            tree[cv].pb(cu);
        }
    }
    /*
        dp[u][0]：以 u 为根的子树内，没有建立任何军营的方案数
        dp[u][1]：以 u 为根的子树内，至少建立了 1 座军营
        且子树内的所有军营通过被看守的树边全部与节点 u 连通的方案数    


        一个分量内不建立军营 ：1
        该分量内建立>=1军营  : (2 ^ noed_cnt[cu]) - 1
        无论建不建军营，内部边均有 (2 ^ egde[u]) 种选法

        初始化: u
        dp[u][0] = 2 ^ egde[u];
        dp[u][1] = ((2 ^ noed_cnt[cu]) - 1 )* (2 ^ egde[u])

        当把一个子节点 v 合并进 u 时(边 (u, v) 是一条树边):
        若 v 子树内无军营：边 (u, v) 可守可不守（2 种选法），贡献为 2 * dp[v][0]
        若 v 子树内有军营：边 (u, v) 必须看守（1 种选法），贡献为 1 * dp[v][1]；

        转移:
        ndp[u][0] = dp[u][0] * (2 * dp[v][0]) 
        ndp[u][1] = dp[u][1] * (2 * dp[v][0] + dp[v][1] ) + dp[u][0] * dp[v][1]

        ! 还要考虑 u 和 其父节点的情况
        
        u != root : ans += dp[u][1] * (2 ^ (m - cnt_e[u] - 1));
        u == root : ans += dp[root][1]

        ans %= mod;
    */
    vector<vii> dp(ebcc_cnt+1, vii(2));

    vii cnt_e(ebcc_cnt+1); //  子树内部的总边数（含内部边和树边）
    int ans = 0;

    auto dfs = [&](auto&self, int u, int fa) -> void {
        dp[u][0] = pw2[edge_cnt[u]];
        dp[u][1] = ((pw2[node_cnt[u]] - 1 + mod) % mod) * pw2[edge_cnt[u]] % mod;
        cnt_e[u] = edge_cnt[u];
        for(int v: tree[u]){
            if(v == fa) continue;
            self(self, v, u);
            vii ndp(2);
            ndp[0] = dp[u][0] * (2 * dp[v][0] % mod) % mod;
            ndp[1] = (dp[u][1] * ((2 * dp[v][0] % mod + dp[v][1]) % mod) % mod + dp[u][0] * dp[v][1] % mod) % mod;
            dp[u] = ndp;
            cnt_e[u] += cnt_e[v] + 1;
        }
        if(u == 1) ans = (ans + dp[1][1]) % mod;
        else {
            ans = (ans + (dp[u][1] * pw2[m - cnt_e[u] - 1] % mod)) % mod;
        }
    };
    dfs(dfs,1,0);
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