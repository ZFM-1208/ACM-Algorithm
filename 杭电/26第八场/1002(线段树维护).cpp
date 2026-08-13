#include<bits/stdc++.h>
using namespace std;
#define rep(i, l, r) for (int i = l; i <= r; i++)
#define vii vector<int>
#define pii pair<int, int>
#define int long long
#define ull unsigned long long
#define pb push_back
#define fi first
#define se second
#define endl '\n'
const int N = 1e6, mod = 1e9+7, inf = 1e18 + 5;
struct Node {
    ull suma; // 区间 a 的和
    ull sumb; // 区间 b 的和
    ull c, d, e; // 复合 Lazy 标记
};

struct SegTree {
    int n;
    vector<int> a, b;
    vector<Node> tree;
    SegTree(int _n){ 
        n = _n; 
        tree.resize((n + 1) * 4); 
        a.resize(n + 1); 
        b.resize(n + 1);
    }
    void push_up(int u){
        tree[u].suma = tree[u << 1].suma + tree[u << 1 | 1].suma;
        tree[u].sumb = tree[u << 1].sumb + tree[u << 1 | 1].sumb;
    }
    void apply(int u, int l, int r, int c, int d, int e) {
        ull len = r - l + 1;
        tree[u].suma += c * tree[u].sumb + d * len;
        tree[u].sumb += e * len;
        tree[u].d += d + c * tree[u].e;
        tree[u].c += c;
        tree[u].e += e;
    }

    void push_down(int u, int l, int r) {
        if (tree[u].c == 0 && tree[u].d == 0 && tree[u].e == 0) return;

        ull mid = (l + r) >> 1;
        apply(u << 1, l, mid, tree[u].c, tree[u].d, tree[u].e);
        apply(u << 1 | 1, mid + 1, r, tree[u].c, tree[u].d, tree[u].e);

        tree[u].c = 0; 
        tree[u].d = 0;
        tree[u].e = 0;
    }

    void build(int u, int l, int r) {
        tree[u].c = 0;
        tree[u].d = 0;
        tree[u].e = 0;
        if(l == r){
            tree[u].suma = a[l];
            tree[u].sumb = b[l];
            return;
        }
        ull mid = (l + r) >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        push_up(u);
    }

    void modify(int u, int l, int r, int ql, int qr, ull c, ull d, ull e) {
        if (ql <= l && r <= qr) {
            apply(u, l, r, c, d, e);
            return;
        }
        push_down(u, l, r); 
        ull mid = (l + r) >> 1;
        if (ql <= mid) modify(u << 1, l, mid, ql, qr, c, d, e);
        if (qr > mid) modify(u << 1 | 1, mid + 1, r, ql, qr, c, d, e);
        push_up(u); 
    }

    ull query(int u, int l, int r, int ql, int qr) {
        if(ql <= l && r <= qr){
            return tree[u].suma;
        }
        push_down(u, l, r); 
        ull mid = (l + r) >> 1;
        ull res = 0;
        if(ql <= mid) res += query(u << 1, l, mid, ql, qr);
        if(qr > mid) res += query(u << 1 | 1, mid + 1, r, ql, qr);
        return res;
    }
};
/*
    * 分析
    题目要求每天开始时所有 1 <= i <= n 都要执行 a[i] <- a[i] + b[i]
    如果直接用普通线段树去修改，每天做一次全局修改 1 ~ n, 复杂度是 O(n)，
    每天都改的话 m 天就是 O(m * n)，必然 TLE。

    * 找ai, bi的线性关系
    <1> 每日 : a[i] = a[i] + b[i]; b[i] = b[i]
    <2> 区间加x : a[i] = a[i]; b[i] = b[i] + x
    ==>
    a' = a + c * b + d;
    b' = b + e

    其中c,d,e是三个系数(线段树Lazy标记)
    c：记录 a 累加了多少次b
    d：记录 a 额外增加了多少常数（例如b 被修改后，对 a 产生的常数贡献）
    e：记录b 累加了多少常数（即对b 的加法）

    * 推导 Lazy 标记的复合（下传）规则
    假设一个节点当前的取值为 (a, b)，已经拥有旧标记 (c1, d1, e1)：
    a' = a + c1 * b + d1
    b' = b + e1
    现在给它施加一个新的标记 (c2, d2, e2)，新值为 (a'', b'')
    a'' = a' + c2 * b' + d2
    b'' = b' + e2
    代入化简得:
    a'' = a + (c1+c2) * b + (d1+d2+c2*e1)
    b'' = b + (e1+e2)

    可得： 
    c_new = c1 + c2;
    d_new = d1 + d2 + c2*e1
    e_new = e1 + e2

    这样，我们就能用 O(1) 复杂度打全局标记，
    把每天的 a[i] = a[i] + b[i] 转化为在根节点1 直接执行一次 apply(1, 1, n, 1, 0, 0)！
*/
void solve(){
    int n,m; cin >> n >> m;
    SegTree st(n);
    rep(i, 1, n) cin >> st.a[i] >> st.b[i];
    st.build(1, 1, n);
    for(int q = 1; q <= m; q++){
        // 每天开始，全局执行 a[i] = a[i] + b[i]
        // 对应 c = 1, d = 0, e = 0
        st.apply(1, 1, n, 1, 0, 0); 
        
        int op; cin >> op;
        if(op == 1){
            // 区间加 x 到 b[i]，对应 c = 0, d = 0, e = x
            ull l,r,x; cin >> l >> r >> x;
            st.modify(1, 1, n, l, r, 0, 0, x);
        } else {
            // 查询区间 a 的和
            ull l,r; cin >> l >> r;
            cout << st.query(1, 1, n, l, r)<< endl;
        }
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();
    return 0;
}
