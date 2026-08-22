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
    int n, m; cin >> n >> m;
    vector<vii> g(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    vii dep(n+1), fa(n+1);
    vii ans;
    bool ok = 0;
    auto dfs = [&](auto& self, int u, int p, int d) -> void {
        dep[u] = d;
        fa[u] = p;
        for(auto v : g[u]){
            if(ok) return;
            if(v == p) continue;
            if(!dep[v]){
                self(self, v, u, d + 1);
            }else if((dep[v] < dep[u]) && (dep[u] - dep[v]) % 2 == 0){
                ok = 1;
                int cur = u;
                // 1 -> 2 -> 3 -> 4 -> 5 -> 1
                while(cur != v){
                    ans.pb(cur);
                    cur = fa[cur];
                }
                ans.pb(v);
                // cout << "ans: ";
                // for(int x: ans) cout << x << " ";
                return;
            }
        }
    };
    
    dfs(dfs, 1, 0, 1);
    if(ok == 0){
        cout << -1 << endl;
        return;
    } 
    cout << ans.size() << endl;
    for(int x: ans) cout << x << " ";
    cout << endl;
    
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