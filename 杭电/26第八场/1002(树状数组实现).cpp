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

double pi = acos(-1);
const int N = 1e6, mod = 1e9+7, inf = 1e18 + 5;

// 单点修改、前缀查询的基础树状数组
struct BIT {
    int n;
    vector<ull> tr;
    BIT(int _n) : n(_n), tr(_n + 1, 0) {}
    int lowbit(int x) { return x & -x; }
    
    void add(int x, ull c) {
        for (int i = x; i <= n; i += lowbit(i)) tr[i] += c;
    }
    
    ull query(int x) {
        ull res = 0;
        for (int i = x; i > 0; i -= lowbit(i)) res += tr[i];
        return res;
    }
};

// 封装：支持【区间加】与【区间求和】的树状数组
struct RangeBIT {
    int n;
    BIT tr1, tr2;
    RangeBIT(int _n) : n(_n), tr1(_n), tr2(_n) {}

    // 区间 [l, r] 加上 c
    void range_add(int l, int r, ull c) {
        tr1.add(l, c);
        tr1.add(r + 1, -c); // ull 下 -c 自动按模 2^64 处理
        tr2.add(l, c * l);
        tr2.add(r + 1, -c * (r + 1));
    }

    // 查询前缀和 [1, x]
    ull query(int x) {
        return tr1.query(x) * (x + 1) - tr2.query(x);
    }

    // 查询区间和 [l, r]
    ull query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

void solve(){
    int n,m; cin >> n >> m;
    RangeBIT H(n), V(n);
    for(int i = 1; i <= n; i++) {
        ull a, b;
        cin >> a >> b;
        H.range_add(i, i, a);
        V.range_add(i, i, b);
    }
    for(int i = 1; i <= m; i++){
        int op; cin >> op;
        if (op == 1) {
            ull l, r, x;
            cin >> l >> r >> x;
            // 在第 t 天修改：
            // V_i += x
            // H_i -= t * x (在 ull 下 -t * x 也是自动处理)
            V.range_add(l, r, x);
            H.range_add(l, r, -i * x);
        } else {
            ull l, r;
            cin >> l >> r;
            // 查询第 t 天的值：Sum(H) + t * Sum(V)
            ull ans = H.query(l, r) + i * V.query(l, r);
            cout << ans << endl;
        }
    }
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