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
const int N = 5e5 + 5, mod = 1e9+7, inf = 1e18 + 5;

void solve(){
    int n; cin >> n;
    using i32 = int32_t;

    vector<i32> phase(n + 1);
    rep(i, 1, n) cin >> phase[i];

    // 输入已经给出父子关系，只存父亲到儿子的边。
    vector<vector<i32>> adj(n + 1);
    vector<i32> fa(n + 1), dep(n + 1), mask(n + 1);

    rep(i, 2, n){
        int p; char c;
        cin >> p >> c;
        adj[p].pb((i32)i);
        fa[i] = (i32)p;
        dep[i] = dep[p] + 1;
        mask[i] = mask[p] ^ (1 << (c - 'a'));
    }

    vector<i32> siz(n + 1, 1), big(n + 1);
    for(int u = n; u >= 2; u--){
        i32 p = fa[u];
        siz[p] += siz[u];
        if(big[p] == 0 || siz[u] > siz[big[p]]) big[p] = (i32)u;
    }

    // ans[u][r]：u 子树中，长度模 3 为 r 的最长合法路径。
    vector<array<i32, 3>> ans(n + 1, array<i32, 3>{-1, -1, -1});
    rep(i, 1, n) ans[i][0] = 0; // 单点路径长度为 0。

    /*
        mx[s][r]：当前 DSU 袋子中，mask=s 且 dep%3=r 的最大深度。
        必须使用 32 位整数，否则仅该数组就会占约 96 MiB。
    */
    static i32 mx[1 << 22][3];
    memset(mx, -1, sizeof(mx));

    auto queryNode = [&](i32 x, i32 root) -> void {
        i32 s = mask[x];

        auto queryMask = [&](i32 target) -> void {
            rep(rem, 0, 2){
                i32 yDepth = mx[target][rem];
                if(yDepth == -1) continue;
                i32 len = dep[x] + yDepth - 2 * dep[root];
                i32 lenRem = len % 3;
                ans[root][lenRem] = max(ans[root][lenRem], len);
            }
        };

        queryMask(s);
        rep(bit, 0, 21) queryMask(s ^ (1 << bit));
    };

    const i32 QUERY = 0, ADD = 1, CLEAR = -1;
    vector<i32> stk;
    stk.reserve(n);

    // 不使用 DFS 序，直接沿儿子边扫描一棵子树。
    auto walkSubtree = [&](i32 start, i32 op, i32 root = 0) -> void {
        stk.clear();
        stk.pb(start);

        while(!stk.empty()){
            i32 u = stk.back();
            stk.pop_back();

            if(op == QUERY){
                queryNode(u, root);
            }else if(op == ADD){
                i32 rem = dep[u] % 3;
                mx[mask[u]][rem] = max(mx[mask[u]][rem], dep[u]);
            }else{
                mx[mask[u]][dep[u] % 3] = -1;
            }

            for(i32 v : adj[u]) stk.pb(v);
        }
    };

    auto processNode = [&](i32 u) -> void {
        // LCA 在某个儿子子树内部的路径，直接继承三个余数答案。
        for(i32 v : adj[u]){
            rep(rem, 0, 2){
                ans[u][rem] = max(ans[u][rem], ans[v][rem]);
            }
        }

        // 袋子中保留着重儿子子树，先处理以 u 为端点的路径。
        queryNode(u, u);
        i32 rem = dep[u] % 3;
        mx[mask[u]][rem] = max(mx[mask[u]][rem], dep[u]);

        // 每棵轻子树先查询、后加入，保证两个端点来自不同分支。
        for(i32 v : adj[u]){
            if(v == big[u]) continue;
            walkSubtree(v, QUERY, u);
            walkSubtree(v, ADD);
        }
    };

    /*
        事件 0：进入节点；事件 1：合并当前节点；事件 2：清空子树。
        用显式栈模拟“轻儿子 -> 重儿子 -> 合并 -> 按需清空”。
    */
    vector<array<i32, 3>> events;
    events.reserve(2 * n + 5);
    events.pb({0, 1, 1});

    while(!events.empty()){
        auto [type, u, keep] = events.back();
        events.pop_back();

        if(type == 2){
            walkSubtree(u, CLEAR);
            continue;
        }
        if(type == 1){
            processNode(u);
            continue;
        }

        if(!keep) events.pb({2, u, 0});
        events.pb({1, u, keep});

        if(big[u]) events.pb({0, big[u], 1});
        for(int i = (int)adj[u].size() - 1; i >= 0; i--){
            i32 v = adj[u][i];
            if(v != big[u]) events.pb({0, v, 0});
        }
    }

    rep(i, 1, n){
        cout << ans[i][phase[i]] << (i == n ? '\n' : ' ');
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}
