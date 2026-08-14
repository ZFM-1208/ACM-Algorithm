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

void solve(){
    int n,m;cin >> n >> m;
    vector<vii> adj(n+1);
    for(int i = 1; i < n; i++){
        int u,v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vector<int> dep(n+1);
    auto dfs = [&] (auto&&self, int u, int fa) -> void {
        dep[u] = dep[fa] + 1;
        for(int v : adj[u]){
            if(v == fa)continue;
            self(self, v, u);
        }
    };
    dfs(dfs, 1, 0);

    vector<vector<pii>> a(n+1);
    for(int i = 1; i <= m; i++){
        int x,t; cin >> x >> t;
        a[x].pb({t + dep[x], i});
    }

    vector<map<int,int>> mp(n+1);
    vector<int> ans(m+1);

    auto dsu = [&] (auto&&self, int u, int p)->void {
        vector<int> dead;
        for(int v: adj[u]){
            if(v == p) continue;
            self(self, v, u);
            if(mp[u].size() < mp[v].size()){
                swap(mp[u], mp[v]);
            }
            for(auto&[k,id] : mp[v]){
                auto it = mp[u].find(k);
                if(it != mp[u].end()){
                    if(it->se != -1){
                        it->se = -1;
                        dead.pb(k);
                    }
                }else{
                    mp[u][k] = id;
                }
            }
            mp[v].clear();
        }

        for(auto& [k,id] : a[u]){
            auto it = mp[u].find(k);
            if(it != mp[u].end()){
                if(it->se != -1){
                    it->se = -1;
                    dead.pb(k);
                }
            }else{
                mp[u][k] = id;
            }
        }

        for(int k : dead){
            mp[u].erase(k);
        }
    };

    dsu(dsu, 1, 0);
    for(auto& [k,id] : mp[1]){
        ans[id] = 1;
    }
    for(int i = 1; i <= m; i++){
        cout << ans[i];
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T = 1;
    // cin >> T;
    while(T--){
        solve();
    }
    return 0;
}