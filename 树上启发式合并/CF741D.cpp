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
    vii fa(n+1), dep(n+1), mask(n+1);
    for(int i = 2; i <= n; i++){
        int p; char c; 
        cin >> p >> c;
        adj[p].pb(i);
        fa[i] = p;
        dep[i] = dep[p] + 1;
        mask[i] = mask[p] ^ (1LL << (c - 'a'));
    }
    vii siz(n+1,1), big(n+1), ans(n+1);
    for(int u = n; u >= 2; u--){
        int p = fa[u];
        siz[p] += siz[u];
        if(big[p] == 0 || siz[u] > siz[big[p]]){
            big[p] = u;
        }
    }
    // mx[s]：当前DSU袋子中, mask 等于 s 的节点的最大深度
    // 如果不存在这样的节点, 则为 -1。
    vector<int> mx(1LL << 22, -1);
    auto query = [&](int x, int root) -> void {
        int s = mask[x];
        if(mx[s] != -1){
            ans[root] = max(ans[root], dep[x] + mx[s] - 2 * dep[root]);
        }
        for(int bit = 0; bit <= 21; bit++){
            int tar = s ^ (1LL << bit);
            if(mx[tar] != -1){
                ans[root] = max(ans[root], dep[x] + mx[tar] - 2 * dep[root]);
            }
        }
    };
    auto change = [&](int st, int op, int root = 0) -> void {
        vector<int> stk;
        stk.pb(st);
        while(!stk.empty()){
            int u = stk.back();
            stk.pop_back();
            if(op == 0) query(u, root);
            else if(op == 1){
                mx[mask[u]] = max(mx[mask[u]], dep[u]);
            }
            else{
                mx[mask[u]] = -1;
            }
            for(int v : adj[u]) stk.pb(v);   
        }
    };
    // keep : 1(处理完当前子树保留信息) / 0 (处理完当前子树后清空信息)
    auto dsu = [&] (auto& self, int u, int keep) -> void {
        for(int v: adj[u]){
            if(v == big[u]) continue;
            self(self, v, 0);
        }
        if(big[u] != 0) self(self, big[u], 1);
        for(int v : adj[u]){
            ans[u] = max(ans[u], ans[v]);
        }
        query(u, u);
        mx[mask[u]] = max(mx[mask[u]], dep[u]);
        for(int v : adj[u]){
            if(v == big[u]) continue;
            change(v, 0, u);
            change(v, 1);
        }
        if(keep == 0) change(u, -1);  
    };
    dsu(dsu,1,0);
    for(int i = 1; i <= n; i++){
        cout << ans[i] << " \n"[i==n];
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