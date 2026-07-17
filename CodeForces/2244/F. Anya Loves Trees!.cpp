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
const int N = 1e6, mod = 1e9+7, inf = 1e18+5;

void solve(){
    int n; cin >> n;
    vector<vector<int>> son(n+1);
    vii p(n+1);
    for(int i = 2; i <= n; i++){
        cin >> p[i];
        son[p[i]].pb(i);
    }
    vii a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    vii mn(n+1, inf), mx(n+1, -inf), cnt(n+1), ok(n+1, 1);
    auto dfs = [&](auto&& self, int u) -> void {
        if(son[u].empty()){
            mn[u] = mx[u] = a[u];
            cnt[u] = 1;
            ok[u] = 1;
            return;
        }
        for(auto v : son[u]){
            self(self, v);
            ok[u] &= ok[v];
            cnt[u] += cnt[v];
            mn[u] = min(mn[u], mn[v]);
            mx[u] = max(mx[u], mx[v]);
        }
        if(mx[u] - mn[u]+1 != cnt[u]){
            ok[u] = 0;
        }
        int sz = son[u].size();
        int cnt = 0;
        for(int i = 0; i < sz; i++){
            int x = son[u][i];
            int y = son[u][(i+1) % sz];
            if(mn[x] > mn[y]){
                cnt++;
            }
        }
        if(cnt > 1){
            ok[u] = 0;
        }
    };
    dfs(dfs, 1);
    cout << (ok[1] ? "YES" : "NO") << endl;
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