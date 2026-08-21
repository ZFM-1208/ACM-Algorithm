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
const int N = 1e6, mod = 998244353, inf = 1e18 + 5;
int ksm(int a, int b){
    int res = 1;
    a %= mod;
    while (b){
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
struct node {
    int len;
    int T1, T2, T3;
    int lz;
    int lzf;
    int lzj;
};

struct SegTree {
    int n;
    vector<node> tr;
    vii a;
    SegTree(int n = 0){ init(n); }

    void init(int _n){
        n = _n;
        a.resize(n + 1);
        tr.resize(4 * n + 5);
    }

    node merge_node(node x, node y){
        node res;
        res.len = x.len + y.len;
        res.T1 = (x.T1 + y.T1) % mod;
        res.T2 = (x.T2 + y.T2) % mod;
        res.T3 = (x.T3 + y.T3) % mod;
        res.lz = 0;
        res.lzf = 0;
        res.lzj = 0;
        return res;
    }

    void push_up(int p){
        int lc = p << 1, rc = p << 1 | 1;
        tr[p].T1 = (tr[lc].T1 + tr[rc].T1) % mod;
        tr[p].T2 = (tr[lc].T2 + tr[rc].T2) % mod;
        tr[p].T3 = (tr[lc].T3 + tr[rc].T3) % mod;
    }

    void apply_set(int p, int v){
        v = (v % mod + mod) % mod;
        int len = tr[p].len % mod;
        int v2 = (v * v) % mod;
        int v3 = (v2 * v) % mod;

        tr[p].T1 = (len * v) % mod;
        tr[p].T2 = (len * v2) % mod;
        tr[p].T3 = (len * v3) % mod;

        tr[p].lz = 1;
        tr[p].lzf = v;
        tr[p].lzj = 0;
    }

    void apply_add(int p, int d){
        d = (d % mod + mod) % mod;
        int len = tr[p].len % mod;
        int d2 = d * d % mod;
        int d3 = d * d % mod * d % mod;
        int T1 = tr[p].T1, T2 = tr[p].T2, T3 = tr[p].T3;

        int T33 = (T3 + 3 * d % mod * T2 % mod + 3 * d2 % mod * T1 % mod + len * d3 % mod) % mod;
        int T22 = (T2 + 2 * d % mod * T1 % mod + len * d2 % mod) % mod;
        int T11 = (T1 + len * d % mod) % mod;
        tr[p].T1 = T11;
        tr[p].T2 = T22;
        tr[p].T3 = T33;

        tr[p].lzj = (tr[p].lzj + d) % mod;
    }

    void push_down(int p){
        int lc = p << 1, rc = p << 1 | 1;
        if(tr[p].lz){
            apply_set(lc, tr[p].lzf);
            apply_set(rc, tr[p].lzf);
            tr[p].lz = 0;
        }
        if(tr[p].lzj != 0){
            apply_add(lc, tr[p].lzj);
            apply_add(rc, tr[p].lzj);
            tr[p].lzj = 0;
        }
    }

    void build(int p, int l, int r){
        tr[p].len = r - l + 1;
        tr[p].lz = 0;
        tr[p].lzf = 0;
        tr[p].lzj = 0;
        if(l == r){
            int v = (a[l] % mod + mod) % mod;
            tr[p].T1 = v;
            tr[p].T2 = v * v % mod;
            tr[p].T3 = v * v % mod * v % mod;
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        push_up(p);
    }

    void change(int p, int l, int r, int ql, int qr, int v){
        if(ql <= l && r <= qr){
            apply_set(p, v);
            return;
        }
        push_down(p);
        int mid = (l + r) >> 1;
        if(ql <= mid) change(p << 1, l, mid, ql, qr, v);
        if(qr > mid) change(p << 1 | 1, mid + 1, r, ql, qr, v);
        push_up(p);
    }

    void add(int p, int l, int r, int ql, int qr, int d){
        if(ql <= l && r <= qr){
            if(d != 0) apply_add(p, d);
            return;
        }
        push_down(p);
        int mid = (l + r) >> 1;
        if(ql <= mid) add(p << 1, l, mid, ql, qr, d);
        if(qr > mid) add(p << 1 | 1, mid + 1, r, ql, qr, d);
        push_up(p);
    }

    node query(int p, int l, int r, int ql, int qr){
        if(ql <= l && r <= qr) return tr[p];
        push_down(p);
        int mid = (l + r) >> 1;
        node res1, res2;
        if(qr <= mid){
            res1 = query(p << 1, l, mid, ql, qr);
            return res1;
        }
        if(ql > mid){
            res2 = query(p << 1 | 1, mid + 1, r, ql, qr);
            return res2;
        }
        return merge_node(query(p << 1, l, mid, ql, qr), query(p << 1 | 1, mid + 1, r, ql, qr));
        // return merge_node(res1, res2);
    }
};

void solve(){
    int n,m; cin >> n >> m;
    SegTree tree(n);
    for(int i = 1; i <= n; i++){
        cin >> tree.a[i];
    }
    tree.build(1,1,n);
    while(m--){
        int op, l, r; 
        cin >> op >> l >> r;
        if(op == 1){
            int k; cin >> k;
            tree.add(1, 1, n, l, r, k);
        }else if(op == 2){
            int k; cin >> k;
            tree.change(1, 1, n, l, r, k);
        }else if(op == 3){
            node res = tree.query(1, 1, n, l, r);
            // cout << "T1: " << res.T1 << endl;
            int m1 = res.T1 % mod * ksm(res.len, mod - 2) % mod;
            // cout << "m1 :" << m1 << endl;
            int m2 = m1 * m1 % mod;
            // int ans = res.T2 % mod * ksm(res.len, mod - 2) % mod - m2 + mod % mod;
            int ans = ((res.T2 % mod * ksm(res.len, mod - 2) % mod - m2) + mod )% mod;
            // cout << "ans : " << ans << endl;
            cout << ans << endl;
        }else if(op == 4){
            node res = tree.query(1, 1, n, l, r);
            // cout << "T1: " << res.T1 << endl;
            int m1 = res.T1 % mod * ksm(res.len, mod - 2) % mod;
            // cout << "m1 :" << m1 << endl;
            int m2 = m1 * m1 % mod;
            int m3 = m1 * m1 % mod * m1 % mod;

            int T3 = (res.T3% mod * ksm(res.len, mod - 2)) % mod;
            int T2 = (3 * m1 % mod * (res.T2 % mod * ksm(res.len, mod - 2) % mod)) % mod;
            int T1 = (2 * m3) % mod;

            int ans = ((T3 - T2 + mod) % mod + T1) % mod;
            cout << ans << endl;
        }
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    return 0;
}