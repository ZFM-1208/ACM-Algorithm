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
// const int N = 1e6, mod = 1e9+7, inf = 1e18 + 5;

void solve(){
    int n,m,mod; 
    cin >> n >> m >> mod;
    vector<vii> adj(n + 1);
    vector<pii> e(m + 1);
    for(int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v);
        e[i] = {u, v};
    }
    vii dfn(n + 1, 0), low(n + 1, 0);
    vii scc_id(n + 1, 0);
    vii scc_sz(1, 0); // 分量大小 (1-based)
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
            scc_sz.pb(cur_sz);
        }
    };
    rep(i, 1, n) {
        if (!dfn[i]) tarjan(tarjan, i);
    }
    vector<vii> dag(scc_cnt + 1);
    for(int i = 1; i <= m; i++){
        auto [u,v] = e[i];
        if (scc_id[u] != scc_id[v]) {
            dag[scc_id[u]].pb(scc_id[v]);
        }
    }
    for(int i = 1; i <= scc_cnt; i++){
        sort(dag[i].begin(), dag[i].end());
        dag[i].erase(unique(dag[i].begin(), dag[i].end()), dag[i].end());
    }
    vii dp(scc_cnt+1);
    vii g(scc_cnt+1);
    for(int u = 1; u <= scc_cnt; u++){
        if(dag[u].size() == 0){
            g[u] = 1;
            dp[u] = scc_sz[u];
            continue;
        }
        int mx = 0;
        for(int v: dag[u]){
            mx = max(mx, dp[v]);
        }
        dp[u] = scc_sz[u] + mx;
        int way = 0;
        for(int v: dag[u]){
            if(dp[v] == mx) {
                way = (way + g[v]) % mod;
            }
        }
        g[u] = way;
    }
    int ansk = 0;
    for(int u = 1; u <= scc_cnt; u++){
        ansk = max(ansk, dp[u]);
    }
    int sum = 0;
    for(int u = 1; u <= scc_cnt; u++){
        if(dp[u] == ansk){
            sum = (sum + g[u]) % mod;
        }
    }
    cout << ansk << endl << sum << endl;
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