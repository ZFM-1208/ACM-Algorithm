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
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<vii> adj(n + 1);
    for(int i = 1; i <= m; i++){
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
    }
    vector<vector<pii>> g(n + 1);
    for(int u = 1; u <= n; u++) {
        if(adj[u].empty()) continue;
        int mn = inf;
        for(int v : adj[u]){
            mn = min(mn, v);
        }
        for(int v : adj[u]){
            if(v == mn){
                g[u].pb({v, 0});
            } else {
                g[u].pb({v, 1}); 
            }
        }
    }
    vii dist(n + 1, inf);
    deque<int> dq;
    dist[s] = 0;
    dq.push_back(s);
    while(!dq.empty()){
        int u = dq.front();
        dq.pop_front();
        if (u == t) break;
        for(auto [v, w] : g[u]){
            if(dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (w == 0) {
                    dq.push_front(v);
                } else {
                    dq.push_back(v);
                }
            }
        }
    }
    if (dist[t] >= inf) {
        cout << -1 << endl;
    } else {
        cout << dist[t] << endl;
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