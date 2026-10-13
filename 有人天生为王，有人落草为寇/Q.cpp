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
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v); 
    }
    vii dfn(n + 1, 0), low(n + 1, 0);
    vii scc_id(n + 1, 0);
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
            while (true) {
                int x = st.top();
                st.pop();
                in_st[x] = false;
                scc_id[x] = scc_cnt;
                if (x == u) break;
            }
        }
    };
    rep(i, 1, n) {
        if (!dfn[i]) tarjan(tarjan, i);
    }
    vector<vii> scc_nodes(scc_cnt+1);
    rep(i, 1, n) {
        scc_nodes[scc_id[i]].pb(i);
    }
    rep(c, 1, scc_cnt) {
        sort(scc_nodes[c].begin(), scc_nodes[c].end());
    }
    cout << scc_cnt << endl;
    vii vis(scc_cnt+1);
    for(int i = 1; i <= n; i++){
        int c = scc_id[i];
        if(!vis[c]){
            vis[c] = 1;
            for(int x: scc_nodes[c]) cout << x << " ";
            cout << endl;
        }
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