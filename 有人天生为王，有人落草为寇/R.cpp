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
    vector<vii> adj(n + 1);
    vector<pii> e(m + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v); 
        e[i] = {u,v}; 
    }
    vii dfn(n + 1, 0), low(n + 1, 0);
    vii scc_id(n + 1, 0);
    vii scc_sz(1,0);
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
    // 同一个 SCC 内的所有点要么“全当明星” 要么“全不当明星”
    // 只有 出度为 0 的超级点 才能当 “全当明星”
    // 分类讨论 出度为 0 的超级点 的个数
    vector<vii> dag(scc_cnt+1); 
    vii out(scc_cnt+1); // 出度
    for(int i = 1; i <= m; i++){
        auto [u,v] = e[i];
        if(scc_id[u] != scc_id[v]){
            dag[scc_id[u]].pb(scc_id[v]);
            out[scc_id[u]]++;
        }
    }
    int cnt = 0;
    int ans = 0;
    for(int i = 1; i <= scc_cnt; i++){
        if(out[i] == 0){
            cnt++;
            ans = scc_sz[i];
        }
    }
    cout << (cnt == 1 ? ans : 0LL) << endl;

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