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
    int n; cin >> n;
    vector<vii> adj(n+1);
    
    // ==================== 圆方树构建模板 ====================
    // 圆点编号: 1 ~ n
    // 方点编号: n + 1 ~ n + bcc_cnt
    // 圆方树总点数: tot = n + bcc_cnt
    int dfn_cnt = 0, bcc_cnt = 0;
    vii dfn(n + 1, 0), low(n + 1, 0);
    stack<int> st;
    
    vector<vii> tree(2 * n + 5); // 圆方树邻接表
    auto tarjan = [&](auto& self, int u, int fa) -> void {
        dfn[u] = low[u] = ++dfn_cnt;
        st.push(u);
        // 孤立点特判（没有连边时直接退栈）
        if(adj[u].empty()){
            st.pop();
            return;
        }

        for(int v : adj[u]) {
            if (v == fa) continue;
            if (!dfn[v]) {
                self(self, v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] >= dfn[u]) {
                    bcc_cnt++;
                    int square = n + bcc_cnt; 
                    tree[u].pb(square);
                    tree[square].pb(u);
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
    rep(i, 1, n) if(!dfn[i]){
        tarjan(tarjan, i, 0);
    }
    int tot = n + bcc_cnt; // 圆方树总点数


}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();
    return 0;
}