#include<bits/stdc++.h>
using namespace std;
#define rep(i, l, r) for (int i = l; i <= r; i++)
#define pii pair<int, int>
#define int long long
#define pb push_back
#define fi first
#define se second
#define endl '\n'
double pi = acos(-1);
const int N = 1e6, mod = 1e9+7, inf = 1e18 + 5;

struct BIT_min {
    int n;
    vector<int> tr;
    BIT_min(int _n) : n(_n), tr(_n + 1, inf) {}
    int lowbit(int x) { return x & -x; }
    
    void update(int x, int c) {
        for (int i = x; i <= n; i += lowbit(i)) tr[i] = min(tr[i], c);
    }
    
    int query(int x) {
        int res = inf;
        for (int i = x; i > 0; i -= lowbit(i)) res = min(res, tr[i]);
        return res;
    }
};

struct BIT_max {
    int n;
    vector<int> tr;
    BIT_max(int _n) : n(_n), tr(_n + 1, -inf) {}
    int lowbit(int x) { return x & -x; }
    
    void update(int x, int c) {
        x = n - x + 1;
        for (int i = x; i <= n; i += lowbit(i)) tr[i] = max(tr[i], c);
    }
    
    int query(int x) {
        x = n - x + 1;
        int res = -inf;
        for (int i = x; i > 0; i -= lowbit(i)) res = max(res, tr[i]);
        return res;
    }
};
void solve(){
    int n,c; cin >> n >> c;
    vector<int> a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    BIT_min tr_min(N+5);
    BIT_max tr_max(N+5);
    for(int i = 1; i <= n; i++){
        int ans = 0;
        int mn = tr_min.query(a[i]);
        if(mn != inf) ans = max(ans, (a[i] - c * i) - mn);
        int mx = tr_max.query(a[i]);
        if(mx != -inf) ans = max(ans, mx - (a[i] + c * i));
        cout << ans << " ";
        tr_min.update(a[i], a[i] - c * i);
        tr_max.update(a[i], a[i] + c * i);
    }
}
void solve1(){
    int n,c; cin >> n >> c;
    int pre_mn = inf, pre_mx = -inf;
    for(int i = 1; i <= n; i++){
        int x; cin >> x;
        pre_mn = min(pre_mn, x - c * i);
        pre_mx = max(pre_mx, x + c * i);
        int ans = max(x - c * i - pre_mn,  pre_mx - (x + c * i));
        cout << ans << " ";
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve1();
    return 0;
}