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
const int inf = 1e18 + 5;
struct SegTree {
    int n;
    vector<int> mn, lazy;
    SegTree(int _n = 0) { init(_n); }
    
    void init(int _n) {
        n = _n;
        mn.assign(4 * n + 5, 0);
        lazy.assign(4 * n + 5, 0);
    }

    void push_up(int p) {
        mn[p] = min(mn[p << 1], mn[p << 1 | 1]);
    }

    void push_down(int p) {
        if (lazy[p] != 0) {
            int lz = lazy[p];
            int lc = p << 1, rc = p << 1 | 1;
            mn[lc] += lz;
            lazy[lc] += lz;
            mn[rc] += lz;
            lazy[rc] += lz;
            lazy[p] = 0;
        }
    }

    void build(int p, int l, int r, const vii& pre) {
        if(l == r){
            mn[p] = pre[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, pre);
        build(p << 1 | 1, mid + 1, r, pre);
        push_up(p);
    }

    void update(int p, int l, int r, int ql, int qr, int val) {
        if (ql <= l && r <= qr) {
            mn[p] += val;
            lazy[p] += val;
            return;
        }
        push_down(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, val);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, val);
        push_up(p);
    }
};

void solve() {
    int n, q; cin >> n >> q;
    vii a(n + 1);
    rep(i,1,n) cin >> a[i];
    string s; cin >> s;
    s = " " + s;
    vii pre(n + 1);
    for(int i = 1; i <= n; i++){
        if(s[i] == '+'){
            pre[i] = pre[i - 1] + a[i];
        }else{
            pre[i] = pre[i - 1] - a[i];
        }
    }
    SegTree tree(n);
    tree.build(1, 1, n, pre);
    while(q--){
        int p; char c;
        cin >> p >> c;
        if(s[p] == c){
            if (tree.mn[1] >= 0) cout << "YES" << endl;
            else cout << "NO" << endl;
        }else{
            int s1,s2;
            if(s[p] == '+') s1 = a[p];
            else s1 = -a[p];
            if(c == '+') s2 = a[p];
            else s2 = -a[p];
            tree.update(1, 1, n, p, n, s2 - s1);
            if (tree.mn[1] >= 0) cout << "YES" << endl;
            else cout << "NO" << endl;
            tree.update(1, 1, n, p, n, -(s2 - s1));
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}