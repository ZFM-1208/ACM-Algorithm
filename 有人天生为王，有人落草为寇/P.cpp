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
    int n,m; cin >> n >> m;
    vii a(n+1);
    rep(i,1,n) cin >> a[i];
    vector<vii> adj(n + 1);
    vector<pii> e(m+1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        e[i] = {u,v};
    }
    vii dfn(n + 1, 0), low(n + 1, 0);
    vii scc_id(n + 1, 0);       // 每个点所属的 SCC 编号 (1 ~ scc_cnt)
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
                low[u] = min(low[u], dfn[v]);
            }
        }

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
        }
    };
    rep(i, 1, n) {
        if(!dfn[i])  tarjan(tarjan, i);
    }
    // 统计每个 SCC 的权值总和
    vii scc_val(scc_cnt+1);
    for(int i = 1; i <= n; i++){
        scc_val[scc_id[i]] += a[i];
    }
    vector<vii> dag(scc_cnt+1); // 建立有向无环图
    vii in_dag(scc_cnt+1); // 入度
    for(int i = 1; i <= m; i++){
        auto [u,v] = e[i];
        if(scc_id[u] != scc_id[v]){
            dag[scc_id[u]].pb(scc_id[v]);
            in_dag[scc_id[v]]++;
        }
    }

    vii dp(n+1,-1); // dp[u]: 求从节点 u 往下走的最大路径权值和
    auto dfs = [&](auto&self , int u) -> int {
        if(dp[u] != -1) return dp[u];
        int mx_nxt = 0;
        for(int v: dag[u]){
            mx_nxt = max(mx_nxt, self(self,v));
        }
        return dp[u] = scc_val[u] + mx_nxt;
    };
    int ans = 0;
    for(int i = 1; i <= scc_cnt; i++){
        if(in_dag[i] == 0){
            ans = max(ans, dfs(dfs, i));
        }
    }
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