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
int fpow(int a,int b){
    int res = 1;
    while(b){
        if(b&1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res % mod;
}

struct SegTree {
    struct Node {
        int sum;
        int lazy;
    };
    int n;
    vector<Node> tree;
    vector<int> a;

    SegTree(int _n) {
        n = _n;
        tree.resize((n + 1) * 4); 
        a.resize(n + 1);
    }

    void push_up(int u) {
        tree[u].sum = tree[u << 1].sum + tree[u << 1 | 1].sum;
    }


    void push_down(int u, int l, int r) {
        if (tree[u].lazy != 0) { 
            int mid = (l + r) >> 1;
            int tag = tree[u].lazy;
            tree[u << 1].sum += tag * (mid - l + 1);
            tree[u << 1].lazy += tag;

            tree[u << 1 | 1].sum += tag * (r - mid);
            tree[u << 1 | 1].lazy += tag; 

            tree[u].lazy = 0;
        }
    }

    void build(int u, int l, int r) {
        tree[u].lazy = 0; 
        if(l == r) {
            tree[u].sum = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        push_up(u);
    }
    void modify(int u, int l, int r, int ql, int qr, int k) {
        if(l >= ql && qr >= r) {
            tree[u].sum += k * (r - l + 1); 
            tree[u].lazy += k;              
            return;
        }
        push_down(u, l, r); 
        
        int mid = (l + r) >> 1;
        if (ql <= mid) modify(u << 1, l, mid, ql, qr, k);
        if (qr > mid) modify(u << 1 | 1, mid + 1, r, ql, qr, k);
        
        push_up(u); 
    }

    int query(int u, int l, int r, int ql, int qr) {
        if(l >= ql && qr <= r) {
            return tree[u].sum;
        }
        
        push_down(u, l, r); 
        int mid = (l + r) >> 1;
        int res = 0;
        if (ql <= mid) res += query(u << 1, l, mid, ql, qr);
        if (qr > mid) res += query(u << 1 | 1, mid + 1, r, ql, qr);
        
        return res;
    }
};
struct SegTree1 {
    struct Node {
        int min_val; // 修改：从 sum 改为 min_val
        int lazy;
    };
    int n;
    const int inf = 1e18 + 5; // 用于最小值初始化的无穷大
    vector<Node> tree;
    vector<int> a;

    SegTree1(int _n) {
        n = _n;
        tree.resize((n + 1) * 4); 
        a.resize(n + 1);
    }

    // 修改 1：向上更新改为取两儿子的较小值
    void push_up(int u) {
        tree[u].min_val = min(tree[u << 1].min_val, tree[u << 1 | 1].min_val);
    }

    // 修改 2：下传标记时，儿子的最小值直接加上 tag，不需要乘以区间长度
    void push_down(int u, int l, int r) {
        if (tree[u].lazy != 0) { 
            int tag = tree[u].lazy;
            
            tree[u << 1].min_val += tag;
            tree[u << 1].lazy += tag;

            tree[u << 1 | 1].min_val += tag;
            tree[u << 1 | 1].lazy += tag; 

            tree[u].lazy = 0;
        }
    }

    void build(int u, int l, int r) {
        tree[u].lazy = 0; 
        if(l == r) {
            tree[u].min_val = a[l]; // 修改
            return;
        }
        int mid = (l + r) >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        push_up(u);
    }

    // 修改 3：修改覆盖区间时，当前区间的最小值直接加上 k
    void modify(int u, int l, int r, int ql, int qr, int k) {
        if(l >= ql && qr >= r) {
            tree[u].min_val += k; // 与区间长度无关
            tree[u].lazy += k;              
            return;
        }
        push_down(u, l, r); 
        
        int mid = (l + r) >> 1;
        if (ql <= mid) modify(u << 1, l, mid, ql, qr, k);
        if (qr > mid) modify(u << 1 | 1, mid + 1, r, ql, qr, k);
        
        push_up(u); 
    }

    // 修改 4：区间查询逻辑修改
    int query(int u, int l, int r, int ql, int qr) {
        // 注意：原代码此处条件判断为 l >= ql && qr <= r 有一处小笔误，已修正为通用标准写法
        if(ql <= l && r <= qr) {
            return tree[u].min_val;
        }
        
        push_down(u, l, r); 
        int mid = (l + r) >> 1;
        int res = inf; // 寻找最小值，初始化为无穷大
        
        if (ql <= mid) res = min(res, query(u << 1, l, mid, ql, qr));
        if (qr > mid) res = min(res, query(u << 1 | 1, mid + 1, r, ql, qr));
        
        return res;
    }
};
void solve() {
    int n, m; cin >> n >> m;
    SegTree st(n);
    for(int i = 1; i <= n; i++) cin >> st.a[i];
    st.build(1, 1, n); 
    while(m--){
        int op; cin >> op;
        if (op == 1) {
            int l, r, k;
            cin >> l >> r >> k;
            st.modify(1, 1, n, l, r, k);
        } else {
            int l, r;
            cin >> l >> r;
            cout << st.query(1, 1, n, l, r) << endl;
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T = 1;
    //cin >> T;
    while(T--)
        solve();
    return 0;
}