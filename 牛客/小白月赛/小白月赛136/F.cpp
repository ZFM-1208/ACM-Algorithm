#include <bits/stdc++.h>
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

struct BIT {
    int n;
    vector<int> tr;
    BIT(int _n) : n(_n), tr(_n+1, 0) {}
    int lowbit(int x) { return x & -x; }
    
    void add(int x, int c) {
        for (int i = x; i <= n; i += lowbit(i)) tr[i] += c;
    }
    
    int query(int x) {
        int res = 0;
        for (int i = x; i > 0; i -= lowbit(i)) res += tr[i];
        return res;
    }
    
    int query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

void solve(){
    int n, w; cin >> n >> w;
    vii c(n+1);
    unordered_map<int,int> cnt;
    for(int i = 1; i <= n; i++){
        cin >> c[i];
        cnt[c[i]]++;
    }
    vector<vii> adj(n+1);
    for(int i = 1; i < n; i++){
        int u, v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    vector<int> dep(n+1), dfn(n+1), out(n+1), siz(n+1, 1), big(n+1);
    vector<vii> fa(n+1, vii(25));
    int ti = 0;

    auto dfs_lca = [&](auto& self, int u, int p) -> void {
        dfn[u] = ++ti;
        dep[u] = dep[p] + 1;
        fa[u][0] = p;
        for (int i = 1; i <= 20; i++) {
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        }
        for (int v : adj[u]) {
            if (v == p) continue;
            self(self, v, u);
            siz[u] += siz[v];
            if (big[u] == 0 || siz[v] > siz[big[u]]) {
                big[u] = v;
            }
        }
        out[u] = ti;
    };
    dfs_lca(dfs_lca, 1, 0);
    
    auto get_lca = [&](int u, int v) -> int {
        if (dep[u] < dep[v]) swap(u, v);
        for (int i = 20; i >= 0; i--) {
            if (dep[fa[u][i]] >= dep[v]) {
                u = fa[u][i];
            }
        }
        if (u == v) return u;
        for (int i = 20; i >= 0; i--) {
            if (fa[u][i] != fa[v][i]) {
                u = fa[u][i];
                v = fa[v][i];
            }
        }
        return fa[u][0];
    };

    vii mn(n+1), mx(n+1);
    for(int i = 1; i <= n; i++) {
        if(mn[c[i]] == 0 || dfn[i] < dfn[mn[c[i]]]) mn[c[i]] = i;
        if(mx[c[i]] == 0 || dfn[i] > dfn[mx[c[i]]]) mx[c[i]] = i;
    }

    vector<vii> jihuo(n+1);
    for(int i = 1; i <= n; i++){
        if(cnt[i]) {
            int p = get_lca(mn[i], mx[i]);
            jihuo[p].pb(cnt[i]);
        }
    }

    BIT bit_cnt(n), bit_sum(n);
    vector<int> freq(n+1, 0);
    auto get_k = [&](int ww) -> int {
        if(ww <= 0) return 0;
        int l = 1, r = n, best = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (bit_sum.query(mid) <= ww) {
                best = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        int ans = bit_cnt.query(best);
        int rem = ww - bit_sum.query(best);
        if(best + 1 <= n && rem){
            ans += min(freq[best + 1], rem / (best + 1));
        }
        return ans;
    };

    auto change = [&](int st, int op) -> void {
        vector<int> stk;
        stk.pb(st);
        while(!stk.empty()){
            int u = stk.back();
            stk.pop_back();
            for(int wt : jihuo[u]){
                if(op == 1){
                    bit_cnt.add(wt, 1);
                    bit_sum.add(wt, wt);
                    freq[wt]++;
                } else {
                    bit_cnt.add(wt, -1);
                    bit_sum.add(wt, -wt);
                    freq[wt]--;
                }
            }
            for(int v : adj[u]){
                if(v != fa[u][0]) stk.pb(v);
            }
        }
    };

    int ans = 0;
    auto dsu = [&](auto& self, int u, int keep) -> void {
        for(int v : adj[u]){
            if(v == fa[u][0] || v == big[u]) continue;
            self(self, v, 0);
        }
        if(big[u] != 0) self(self, big[u], 1);
        
        for(int v : adj[u]){
            if(v == fa[u][0] || v == big[u]) continue;
            change(v, 1);
        }
        for(int wt : jihuo[u]){
            bit_cnt.add(wt, 1);
            bit_sum.add(wt, wt);
            freq[wt]++;
        }

        int k = get_k(w);
        ans = max(ans, dep[u] * k);

        if(keep == 0)  change(u, -1);
    };
    dsu(dsu, 1, 1);
    cout << ans << endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T = 1;
    if (cin >> T) {
        while (T--) solve();
    }
    return 0;
}