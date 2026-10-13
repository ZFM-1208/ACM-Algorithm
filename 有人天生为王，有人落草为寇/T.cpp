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
    vector<vector<pii>> adj(n+1);
    vector<array<int,3>> e(m+1);
    for(int i = 1; i <= m; i++){
        int u,v,w; cin >> u >> v >> w;
        e[i] = {u,v,w};
        adj[u].pb({v,w});
    }
    int s; cin >> s;
    vii dfn(n + 1, 0), low(n + 1, 0);
    vii scc_id(n + 1, 0);       
    vector<bool> in_st(n + 1, false);
    stack<int> st;
    int dfn_cnt = 0, scc_cnt = 0;

    auto tarjan = [&](auto& self, int u) -> void {
        dfn[u] = low[u] = ++dfn_cnt;
        st.push(u);
        in_st[u] = true;

        for (auto [v,w] : adj[u]) {
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
    vii val;
    int k = 0;
    while(1){
        int t = k * (k+1) / 2;
        val.pb(t);
        if(t > 1e8+7) break;
        k++;
    }
    vii sum(val.size());
    for(int i = 1; i < sum.size(); i++){
        sum[i] = sum[i-1] + val[i];
    }
    auto get = [&](int w) -> int {
        if(w == 0) return 0;
        int k = upper_bound(val.begin(), val.end(),w) - val.begin();
        k--;
        return (k+1)*w - sum[k];
    };

    vii scc_val(scc_cnt+1);
    vector<vector<pii>> dag(scc_cnt+1);
    for(int i = 1; i <= m; i++){
        auto [u,v,w] = e[i];
        if(scc_id[u] == scc_id[v]){
            scc_val[scc_id[u]] += get(w);
        }else{
            dag[scc_id[u]].pb({scc_id[v],w});
        }
    }
    vii dp(scc_cnt+1);
    for(int i = 1; i <= scc_cnt; i++){
        int mx_nxt = 0;
        for(auto[v,w]: dag[i]){
            mx_nxt = max(mx_nxt, w + dp[v]);
        }
        dp[i] = scc_val[i] + mx_nxt;
    }
    cout << dp[scc_id[s]] << endl;

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