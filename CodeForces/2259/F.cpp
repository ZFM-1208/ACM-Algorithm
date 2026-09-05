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

struct SegTree {
    int n;
    vector<int> sum, mx, lz;

    SegTree(int n = 0) { init(n); }

    void init(int _n) {
        n = _n;
        sum.assign(4*n+7, 0);
        mx.assign(4*n+7, 0);
        lz.assign(4*n+7, 0);
    }

    void pushup(int p) {
        sum[p] = sum[p << 1] + sum[p << 1 | 1];
        mx[p] = max(mx[p << 1], mx[p << 1 | 1]);
    }

    void apply(int p, int l, int r, int v) {
        sum[p] += v * (r - l + 1);
        mx[p] += v;
        lz[p] += v;
    }

    void pushdown(int p, int l, int r) {
        if(lz[p]){
            int mid = (l + r) >> 1;
            apply(p << 1, l, mid, lz[p]);
            apply(p << 1 | 1, mid + 1, r, lz[p]);
            lz[p] = 0;
        }
    }

    void build(int p, int l, int r, const vector<int>& a) {
        if(l == r){
            sum[p] = mx[p] = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a);
        build(p << 1 | 1, mid + 1, r, a);
        pushup(p);
    }

    void update(int p, int l, int r, int ql, int qr, int v) {
        if(ql <= l && r <= qr){
            apply(p, l, r, v);
            return;
        }
        pushdown(p, l, r);
        int mid = (l + r) >> 1;
        if(ql <= mid) update(p << 1, l, mid, ql, qr, v);
        if(qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, v);
        pushup(p);
    }

    int query(int p, int l, int r, int ql, int qr) {
        if(ql > r || qr < l || ql > qr) return 0;
        if(ql <= l && r <= qr) return sum[p];
        pushdown(p, l, r);
        int mid = (l + r) >> 1;
        int res = 0;
        if(ql <= mid) res += query(p << 1, l, mid, ql, qr);
        if(qr > mid) res += query(p << 1 | 1, mid + 1, r, ql, qr);
        return res;
    }

    int cz(int p, int l, int r, int ql) {
        if(r < ql || mx[p] <= 0) return 0;
        if(l == r) return l;
        pushdown(p, l, r);
        int mid = (l + r) >> 1;
        int res = cz(p << 1 | 1, mid + 1, r, ql);
        if (res) return res;
        return cz(p << 1, l, mid, ql);
    }
};

/*
    '1':
    111000 -- 110001
    11000011001  -- 10000110011

    '0':
    111000 -- 011100
    11000011001  --  01100001101
*/
void solve(){
    int n; cin >> n;
    vii a(n+1);
    rep(i,1,n) cin >> a[i];
    string s; cin >> s;
    s = " " + s;
    int ans = 0;
    vii c;
    int cn1 = 0;
    for(int i = 1; i <= n; i++){
        if(a[i] == 0){
            c.pb(cn1);
        }else{
            cn1++;
        }
    }
    if(c.size() == 0){
        rep(i, 0, n) cout << 0 << " \n"[i == n];
        return;
    }
    sort(c.begin(), c.end(), greater<int>());
    int m = c.size();
    vii df(m + 1);
    rep(i, 1, m) df[i] = c[i - 1];
    SegTree tree(m);
    tree.build(1, 1, m, df);
    int l = 1;
    cout << tree.query(1, 1, m, l, m);
    for(int i = 1; i <= n; i++){
        if(s[i] == '1'){
            if(l <= m){
                int R = tree.cz(1, 1, m, l);
                if(R >= l){
                    tree.update(1, 1, m, l, R, -1);
                }
            }
        }else{
            l++;
        }
        if(l <= m){
            cout << " " << tree.query(1, 1, m, l, m);
        }else{
            cout << " " << 0;
        }
    }
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