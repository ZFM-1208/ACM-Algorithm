// 若图是无向图，就可以这么做
// struct DSU {
//     vector<int> fa;
//     DSU(int n) {
//         fa.resize(n+1);
//         iota(fa.begin(), fa.end(), 0);
//     }
//     int find(int x){
//         return x == fa[x] ? x : fa[x] = find(fa[x]);
//     }
    
//     void link(int x, int y){
//         int fx = find(x);
//         int fy = find(y);
//         if(fx != fy){
//             fa[fx] = fy;
//         }
//     }
// };

// void solve(){
//     int n,m,q; cin >> n >> m >> q;
//     vector<vii> adj(n+1);
//     for(int i = 1; i <= m; i++){
//         int u,v; cin >> u >> v;
//         adj[u].pb(v);
//     }
//     vector<int> p(q+1);
//     vector<int> vis(n+1);
//     for(int i = 1; i <= q; i++) {
//         cin >> p[i];
//         vis[p[i]] = 1;
//     }
//     DSU dsu(n+1);
//     for(int i = 1; i <= n; i++){
//         if(vis[i] == 0){
//             for(int x: adj[i]){
//                 dsu.link(x , i);
//             }
//         }
//     }
//     // cout << dsu.find(1) << " " << dsu.find(n) << endl;
//     if(dsu.find(1) == dsu.find(n)){
//         cout << "YES" << endl;
//         return;
//     }    
//     for(int i = q; i >= 1; i--){
//         for(int x: adj[p[i]]){
//             dsu.link(x,p[i]);
//         }
//         if(dsu.find(1) == dsu.find(n)){
//             cout << q-1 << endl;
//             return;
//         }   
//     }
//     cout << "NO" << endl;
// }



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
    int n,m,q; cin >> n >> m >> q;
    vector<vii> adj(n+1);
    for(int i = 1; i <= m; i++){
        int u,v; cin >> u >> v;
        adj[u].pb(v);
    }
    vii p(q+1), del(n+1); // del[u] = 1: u的出边被删除了
    for(int i = 1; i <= q; i++){
        cin >> p[i];
        del[p[i]] = 1;
    }
    vii can(n+1), vis(n+1); // can[u] = 1: 表示 u 从 1 号点可达
    // vis[u] = 1: 表示 u 已经扫描过
    queue<int> pq;
    can[1] = 1;
    pq.push(1);
    while(!pq.empty()){
        int u = pq.front(); pq.pop();
        if(vis[u]) continue;
        vis[1] = 1;
        for(int v: adj[u]){
            if(can[v] == 0){
                can[v] = 1;
                if(vis[v] == 0 && del[v] == 0){
                    pq.push(v);
                }
            }
        }
    }
    if(can[n] == 1){
        cout << "YES" << endl;
        return;
    }
    for(int i = q; i >= 1; i--){
        del[p[i]] = 0;
        if(can[p[i]] && vis[p[i]] == 0){
            pq.push(p[i]);
            while(!pq.empty())
            {
                int u = pq.front(); pq.pop();
                if(vis[u]) continue;
                vis[1] = 1;
                for(int v: adj[u]){
                    if(can[v] == 0){
                        can[v] = 1;
                        if(vis[v] == 0 && del[v] == 0){
                            pq.push(v);
                        }
                    }
                }
            } 
            if(can[n]) {
                cout << i-1 << endl;
                return;
            }
        }
    }
    cout << "NO" << endl;
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