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
struct node {
    int cnt[3];
    int l[3];
    int r[3];
    int lz;
};
string s;
struct SegTree {
    int n;
    vector<node> tr;

    SegTree(int n = 0) { init(n); }

    void init(int _n) {
        n = _n;
        tr.resize(4 * n + 5);
    }
    void push_up(int p) {
        for(int k = 0; k < 3; k++){
            tr[p].cnt[k] = tr[p << 1].cnt[k] + tr[p << 1 | 1].cnt[k];
            if(tr[p << 1].r[k] == 1 && tr[p << 1 | 1].l[k] == 1) {
                tr[p].cnt[k]--;
            }
            tr[p].l[k] = tr[p << 1].l[k];
            tr[p].r[k] = tr[p << 1 | 1].r[k];
        }
    }

    void push_down(int p) {
        if(tr[p].lz == 0)  return;
        node zhuo = tr[p << 1];
        node you = tr[p << 1 |1];
        for(int k = 0; k < 3; k++){
            int op = (k + tr[p].lz) % 3;
            tr[p << 1].cnt[k] = zhuo.cnt[op];
            tr[p << 1].l[k] = zhuo.l[op];
            tr[p << 1].r[k] = zhuo.r[op];
            int op1 = (k + tr[p].lz) % 3;
            tr[p << 1 | 1].cnt[k] = you.cnt[op1];
            tr[p << 1 | 1].l[k] = you.l[op1];
            tr[p << 1 | 1].r[k] = you.r[op1];
        }
        tr[p << 1].lz = (tr[p << 1].lz + tr[p].lz) % 3;        
        tr[p << 1 | 1].lz = (tr[p << 1 | 1].lz + tr[p].lz) % 3;    
        tr[p].lz = 0;
    }

    void build(int p, int l, int r) {
        tr[p].lz = 0;
        if (l == r) {
            int c = s[l] - 'A'; // 0 1 2
            for(int k = 0; k < 3; k++) {
                int ok = 0;
                if((c + k) % 3 == 0) ok = 1;
                tr[p].cnt[k] = ok;
                tr[p].l[k] = ok;
                tr[p].r[k] = ok;
            }
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        push_up(p);
    }

    void update(int p, int l, int r, int ql, int qr){
        if(ql <= l && r <= qr){
            node zj = tr[p];
            for(int k = 0; k < 3; k++){
                tr[p].cnt[k] = zj.cnt[(k + 1) % 3];
                tr[p].l[k] = zj.l[(k + 1) % 3];
                tr[p].r[k] = zj.r[(k + 1) % 3];
            }
            tr[p].lz = (tr[p].lz + 1) % 3;
            return;
        }
        push_down(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr);
        push_up(p);
    }
};

void solve(){
    int n, q; cin >> n >> q;
    cin >> s; s = " " + s; 
    SegTree tree(n);
    tree.build(1,1,n);
    while(q--){
        int op; cin >> op;
        if(op == 1){
            int l, r;cin >> l >> r;
            tree.update(1,1,n,l,r);
        }else{
            cout << tree.tr[1].cnt[0] << endl;
        }
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