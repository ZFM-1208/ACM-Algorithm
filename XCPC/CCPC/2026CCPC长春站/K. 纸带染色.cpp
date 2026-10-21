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

void solve(){
    int n,m,q; cin >> n >> m >> q;
    vii o(m+1),x(m+1);
    rep(i,1,m) cin >> o[i] >> x[i];
    vii nxt(m+1,m+1);// 每个操作的存活期是[i,nxt[i] - 1] 且 还有空白格子
    vii st0,st1;
    for(int i = m; i >= 1; i--){
        if(o[i] == 0){
            while(!st0.empty() && x[st0.back()] < x[i]) st0.pop_back();
            if (!st0.empty()) nxt[i] = st0.back();
            st0.pb(i);
        }else{
            while (!st1.empty() && x[st1.back()] > x[i]) st1.pop_back();
            if (!st1.empty()) nxt[i] = st1.back();
            st1.pb(i);
        }
    }
    /*
        对于一个固定的右端点 R，操作 i 想要“活过同侧吞噬”，当且仅当 nxt[i] > R
        操作i在 nxt[i] 的时候就会时效 
        * 我们把复杂的“纸带覆盖过程”，转化成了一个极其纯粹的静态条件
        在以 R 为右端点的区间里，有哪些操作 i 满足 nxt[i] > R 且没有被全盘覆盖
        既然条件变成了 nxt[i] > R，那我们就可以开始枚举 R 了(也就是离线扫描线)：
        当 R 从 1 变到 m 时：
        <1>: 新增了一个操作 R，它在树状数组的第 R 个位置上标为 1（代表活着的候选人）
        <2>: 有些老操作在这一刻迎来了它们的死亡时间（即 nxt[old_i] == R），
             它们的存活期到了，我们在树状数组的对应位置上标为 -1。
        此时此刻(在右端点为 R 的前提下)，树状数组里所有值为 1 的下标，全都是还没有被同侧吞噬的“活着的合法操作”！

        * 对于一个询问 (L, R)，我们想知道有多少个活着的合法操作
        <1> i >= L 
        <2> i >= B (B 是 满格边界, 所有 < B 的操作都因为纸带满了而抢不到格子，彻底失效)
        ===> i >= max(L, B)

        最终合法的操作下标范围，就是一个闭区间 [max(L, B), R]

        那这个B怎么求？ B 由纸带左右两边覆盖进度max0, min1决定。对着R增大,它具有单调性，可以用二分配合单调栈来去算B


    */
    vector<vii> kill(m+2);
    for(int i = 1; i <= m; i++){
        if(nxt[i] <= m) kill[nxt[i]].pb(i);
    }
    vector<vector<pii>> qs(m+1);
    for(int i = 1; i <= q; i++){
        int l,r; cin >> l >> r;
        qs[r].pb({l,i});
    }
    BIT bit(m);

    // s0里存的是当前所有的“前缀操作老大”（下标递增，x 值递减）
    // s1里存的是当前所有的“后缀操作老大”（下标递增，x 值递增）
    vii s0, s1;  
    vii ans(q + 1, 0);

    auto get_max0 = [&](int idx) -> int {
        auto it = lower_bound(s0.begin(), s0.end(), idx);
        if (it == s0.end()) return 0;
        return x[*it];
    };

    auto get_min1 = [&](int idx) -> int {
        auto it = lower_bound(s1.begin(), s1.end(), idx);
        if (it == s1.end()) return n + 1;
        return x[*it];
    };

    for(int R = 1; R <= m; R++){
        for(int id : kill[R]) {
            bit.add(id, -1);
        }
        bit.add(R, 1);
        if (o[R] == 0) {
            while (!s0.empty() && x[s0.back()] <= x[R]) s0.pop_back();
            s0.pb(R);
        } else {
            while (!s1.empty() && x[s1.back()] >= x[R]) s1.pop_back();
            s1.pb(R);
        }
        if (qs[R].empty()) continue;
        /*
            [mid, R] 可以使格子铺满,找最大的合法mid
        */
        int low = 1, high = R, B = 0;
        while (low <= high) {
            int mid = (low + high) >> 1;
            
            if (get_max0(mid) >= get_min1(mid) - 1) {
                B = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        for (auto [L, qid] : qs[R]) {
            int st = max(L, B);
            ans[qid] = bit.query(st, R);
        }
    }
    rep(j, 1, q) {
        cout << ans[j] << endl;
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