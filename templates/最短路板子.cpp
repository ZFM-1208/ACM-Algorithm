
#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define pii pair<int,int>
#define endl '\n'
using namespace std;
const int mod1 = 1e9 + 7;
const int mod2 = 998244353;
const int inf = 1e18;
const int N = 3000;
int n,m,st,ed;
int dist[N];
int g[N][N];
bool vis[N];
void dijkstra(){
    fill(dist,dist+n+1,inf);
    fill(vis,vis+n+1,false);
    dist[st] = 0;
    for(int i = 1;i <= n;i++){
        int v = -1;
        for(int j = 1;j <= n;j++){
            if(!vis[j] && (v == -1 || dist[j] < dist[v])){
                v = j;
            }
        }
        if(v == -1 || dist[v] == inf) break;
        vis[v] = true;
        for(int j = 1;j <= n;j++){
            if(!vis[j] && g[v][j] != inf){
                if(dist[v] + g[v][j] < dist[j]){
                    dist[j] = dist[v] + g[v][j];
                }
            }
        }
    }
}
void solve() {
    cin >> n >> m >> st >> ed;
    for(int i = 1;i <= n;i++){
        fill(g[i],g[i]+N+1,inf);
        g[i][i] = 0;
    }
    while(m--){
        int u,v,w; cin >> u >> v >> w;
        g[u][v] = g[v][u] = min(g[u][v],w);
    }
    dijkstra();
    cout << dist[ed] << endl;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int T = 1;
    //cin >> T;
    while (T--) solve();
    return 0;
}
