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

struct node {
    int sum;
    int l, r;
    int lz;
    int cnt;
    int ok;
};

struct SegTree {
    int n;
    vector<node> tr;
    vii a;
    SegTree(int n = 0) { init(n); }

    void init(int _n) {
        n = _n;
        tr.assign(4 * n + 5, {0, 0, 0, 0, 0, 0});
        a.assign(n + 1, 0);
    }

    void push_up(int p) {
        tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum + (tr[p << 1].r != tr[p << 1 | 1].l);
        tr[p].l = tr[p << 1].l;
        tr[p].r = tr[p << 1 | 1].r;
    }

    void push_down(int p) {
        int pl = p << 1, pr = p << 1 | 1;
        if (tr[p].ok) {
            tr[pl].ok = tr[pr].ok = 1;
            tr[pl].lz = tr[pr].lz = tr[p].lz;
            tr[pl].l = tr[pl].r = tr[p].lz;
            tr[pr].l = tr[pr].r = tr[p].lz;
            tr[pl].sum = tr[pr].sum = 0;
            tr[pl].cnt = tr[pr].cnt = 0;
            tr[p].ok = 0;
        }
        if (tr[p].cnt) {
            if (tr[pl].ok) tr[pl].lz ^= 1;
            else tr[pl].cnt ^= 1;
            tr[pl].l ^= 1;
            tr[pl].r ^= 1;

            if (tr[pr].ok) tr[pr].lz ^= 1;
            else tr[pr].cnt ^= 1;
            tr[pr].l ^= 1;
            tr[pr].r ^= 1;

            tr[p].cnt = 0;
        }
    }

    void build(int p, int l, int r) {
        tr[p].lz = tr[p].cnt = tr[p].ok = 0;
        if (l == r) {
            tr[p].l = a[l];
            tr[p].r = a[l];
            tr[p].sum = 0;
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        push_up(p);
    }

    void fg(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) {
            tr[p].ok = 1;
            tr[p].lz = v;
            tr[p].l = tr[p].r = v;
            tr[p].cnt = 0;
            tr[p].sum = 0;
            return;
        }
        push_down(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) fg(p << 1, l, mid, ql, qr, v);
        if (qr > mid) fg(p << 1 | 1, mid + 1, r, ql, qr, v);
        push_up(p);
    }

    void qf(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            if (tr[p].ok) tr[p].lz ^= 1;
            else tr[p].cnt ^= 1;
            tr[p].l ^= 1;
            tr[p].r ^= 1;
            return;
        }
        push_down(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) qf(p << 1, l, mid, ql, qr);
        if (qr > mid) qf(p << 1 | 1, mid + 1, r, ql, qr);
        push_up(p);
    }

    node query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tr[p];
        push_down(p);
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        node res1 = query(p << 1, l, mid, ql, qr);
        node res1 = query(p << 1 | 1, mid + 1, r, ql, qr);
        node res;
        res.sum = res1.sum + res1.sum + (res1.r != res1.l);
        res.l = res1.l;
        res.r = res1.r;
        return res;
    }
};

void solve() {
    int n, q;
    if (!(cin >> n >> q)) return;
    SegTree tree(n);
    for (int i = 1; i <= n; i++) cin >> tree.a[i];
    tree.build(1, 1, n);
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int l, r, x; cin >> l >> r >> x;
            tree.fg(1, 1, n, l, r, x);
        } else if (op == 2) {
            int l, r; cin >> l >> r;
            tree.qf(1, 1, n, l, r);
        } else {
            int l, r; cin >> l >> r;
            cout << tree.query(1, 1, n, l, r).sum << endl;
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T = 1;
    if (cin >> T) {
        while (T--) solve();
    }
    return 0;
}
