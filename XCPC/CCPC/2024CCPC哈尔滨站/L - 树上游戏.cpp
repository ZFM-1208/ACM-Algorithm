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
struct node{
    int to,w;
};
void solve(){
    int L,R; cin >> L >> R;
    map<int, vector<node>> g;
    int mx = -1;
    int cnt = 0;
    auto dfs = [&](auto& self, int u, int bit, int l, int r) -> void {
        int mid = 1 << bit;
        // [0, mid - 1]
        if (l <= mid - 1) {
            int l0 = l, r0 = min(r, mid - 1);
            if (l0 == 0 && r0 == mid - 1) {
                g[u].push_back({-1 - bit, 0});
                mx = max(mx, bit);
            } else {
                int v = ++cnt;
                g[u].push_back({v, 0});
                self(self, v, bit - 1, l0, r0);
            }
        }

        // [mid, 2 * mid - 1]
        if (r >= mid) {
            int l1 = max(l, mid) - mid, r1 = r - mid;
            if (l1 == 0 && r1 == mid - 1) {
                g[u].push_back({-1 - bit, 1});
                mx = max(mx, bit);
            } else {
                int v = ++cnt;
                g[u].push_back({v, 1});
                self(self, v, bit - 1, l1, r1);
            }
        }
    };
    for(int len = 1; len <= 20; len++){
        int lo = max(L,1LL << (len - 1));
        int hi = min(R, (1LL << len) - 1);
        if(lo > hi) continue;
        int rlen = len - 1;
        if(len == 1){
            g[0].pb({-1,1});
            mx = max(mx, 0LL);
            continue;
        }
        int l = lo - (1LL << (len - 1));
        int r = hi - (1LL << (len - 1));
        if(l == 0 && r == (1LL << (len - 1)) - 1){
            g[0].pb({-1-(len-1),1});
            mx = max(mx, len - 1);
        }else{
            cnt++;
            g[0].pb({cnt, 1});
            dfs(dfs, cnt, len - 1 - 1, l, r);
        }
    }
    for (int d = mx; d >= 1; d--) {
        g[-1 - d].push_back({-1 - (d - 1), 0});
        g[-1 - d].push_back({-1 - (d - 1), 1});
    }
    map<int, int> id;
    int n = 0;
    id[0] = ++n;
    for (int i = 1; i <= cnt; i++) {
        id[i] = ++n;
    }
    for (int d = mx; d >= 0; d--) {
        id[-1 - d] = ++n; 
    }

    vector<vector<pii>> adj(n + 1);
    for (auto& [u, edges] : g){
        for (auto& e : edges) {
            adj[id[u]].push_back({id[e.to], e.w});
        }
    }
    cout << n << "\n";
    for (int i = 1; i <= n; i++) {
        cout << adj[i].size();
        for (auto& [v, w] : adj[i]) {
            cout << " " << v << " " << w;
        }
        cout << "\n";
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