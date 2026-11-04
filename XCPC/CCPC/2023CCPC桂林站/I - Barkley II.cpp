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
struct BIT {
    int n;
    vector<int> tr;
    BIT(int _n) : n(_n), tr(_n + 1, 0) {}
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
struct node{
    int l,x;
};
int lsp[N];
void solve(){
    int n,m; cin >> n >> m;
    vii a(n+1), vis(n+3);

    for(int i = 1; i <= n; i++){
        cin >> a[i];
        if(a[i] <= n+1) vis[a[i]] = 1;
    }
    int mex = 1;
    while(vis[mex]) mex++;
    int x0 = min(mex,m+1);
    vector<vector<node>> cun(n+1); // 按右端点存
    cun[n].pb({1,x0});
    vector<pii> pts;
    pts.reserve(n);
    rep(i, 1, n) pts.pb({a[i], i});
    sort(pts.begin(), pts.end());
    int sz = pts.size();
    for(int i = 0; i < sz; ){
        int j = i;
        while(j < sz && pts[j].fi == pts[i].fi) j++;
        int val = pts[i].fi;
        if(pts[i].se > 1) cun[pts[i].se - 1].pb({1, val});
        for(int k = i; k <= j-2; k++){
            int l = pts[k].se + 1;
            int r = pts[k+1].se - 1;
            cun[r].pb({l,val});
        }
        if(pts[j-1].se < n) cun[n].pb({pts[j-1].se+1, val});
        i = j;
    }
    BIT bit(n);
    int ans = -inf;
    for(int r = 1; r <= n; r++){
        int v = a[r];
        if (lsp[v] != 0) {
            bit.add(lsp[v], -1);
        }
        bit.add(r, 1);
        lsp[v] = r;

        for(const auto& [l,x] : cun[r]){
            ans = max(ans, bit.query(l, r) - x);
        }
    }
    for(int i = 1; i <= n; i++) lsp[a[i]] = 0;
    cout << ans << endl;

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