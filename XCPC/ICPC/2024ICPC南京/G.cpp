#include<bits/stdc++.h>
using namespace std;
#define rep(i, l, r) for (int i = l; i <= r; i++)
#define vii vector<int>
#define pii pair<int, int>
#define int long long
#define pb push_back
#define fi first
#define se second
// #define endl '\n'
double pi = acos(-1);
const int N = 1e6, mod = 1e9+7, inf = 1e18 + 5;
int ask(int u, int v) {
    cout << "? " << u << " " << v << endl;
    int res; cin >> res;
    return res;
}
void answer(int s){
    cout << "! " << s << endl;
}
/*
【解题思路总结：树上点分治（重心） + 二叉树邻居交互三分】

1. 题目瓶颈与转化：
   - 交互库是自适应的，且询问次数上限为 ⌊log2 n⌋。
   - 这要求每一轮询问必须无条件将当前候选节点集合的大小严格减半（|V'| <= ⌊|V| / 2⌋）。
   - 给定的是二叉树，每个节点的度数至多为 3（最多 2 个儿子 + 1 个父亲）。

2. 树的重心性质：
   - 在当前候选节点构成的连通子树中，找到重心 c。
   - 删去重心 c 后，分裂出的连通分支至多只有 3 个，且每个分支的大小均 <= ⌊|V| / 2⌋。

3. 构造询问（3 种反馈精确对应 3 个分支）：
   - 将重心 c 分裂出的分支按节点数量降序排序：S1 >= S2 >= S3（S1 + S2 + S3 = |V| - 1）。
   - 选取前两大分支直接与 c 相邻的节点 u1, v1，发起询问 ask(u1, v1)：
     * res == 0：u1 更近 -> 目标点落在分支 1（规模为 S1 <= ⌊|V| / 2⌋）。
     * res == 2：v1 更近 -> 目标点落在分支 2（规模为 S2 <= ⌊|V| / 2⌋）。
     * res == 1：距离相等 -> 目标点必为重心 c 自身或落在分支 3 中（规模为 S3 + 1 <= ⌊|V| / 2⌋）。

4. 递归与终止边界：
   - |V| == 1：集合仅剩 1 点，直接输出 ! V[0]。
   - |V| == 2：集合剩 2 点，直接发起 1 次询问 ask(V[0], V[1]) 决出答案。
   - |V| >= 3：点分治递归缩小候选集，至多 ⌊log2 n⌋ 轮必定收敛。

5. 交互注意事项：
   - 每次询问与最终回答输出后必须使用 endl（或 fflush）刷新缓冲区，避免交互死锁导致 TLE。
*/
void solve(){
    int n; cin >> n;
    vector<vii> a(n+1);
    for(int i = 1; i <= n; i++){
        int x,y; cin >> x >> y;
        if(x != 0) a[i].pb(x),a[x].pb(i);
        if(y != 0) a[i].pb(y),a[y].pb(i);
    }
    vii v;
    for(int i = 1; i <= n; i++) v.pb(i);
    vii vis(n+1,1);
    
    while(1){
        if(v.size() == 1){
            answer(v.front());
            return;
        }else if(v.size() == 2){
            int res = ask(v[0], v[1]);
            if(res == 0) answer(v[0]);
            else answer(v[1]);
            return;
        }else{
            auto get_zx = [&]() -> int {
                int tot = v.size();
                int zx = -1;
                int MX = inf;

                auto dfs = [&](auto self, int u, int fa) -> int {
                    int sz = 1;
                    int mx = 0;
                    for(int v : a[u]){
                        if(v != fa && vis[v]){
                            int hsz = self(self, v, u);
                            sz += hsz;
                            mx = max(mx, hsz);
                        }
                    }
                    mx = max(mx, tot - sz);
                    if (mx < MX) {
                        MX = mx;
                        zx = u;
                    }
                    return sz;
                };

                dfs(dfs, v[0], 0);
                return zx;
            };

            int c = get_zx(); // 重心
            vis[c] = 0;

            struct node{
                int lj; // 重心邻居
                vii nodes;
            };
            vector<node> brc;

            auto collect = [&](auto self, int u, int fa, vii& nodes) -> void {
                nodes.pb(u);
                for(int v: a[u]){
                    if(v != fa && vis[v] == 1){
                        self(self, v, u, nodes);
                    }
                }
            };
            for(int v: a[c]){
                if(vis[v] == 0) continue;
                node tp;
                tp.lj = v;
                collect(collect, v, 0, tp.nodes);
                brc.pb(tp);
            }
            sort(brc.begin(), brc.end(), [](const node& x, const node& y) {
                return x.nodes.size() > y.nodes.size();
            });
            int u1 = brc[0].lj;
            int v1 = brc[1].lj;
            int res = ask(u1, v1);
            for(int x: v) vis[x] = 0;
            vii nxt_v;
            if(res == 0){
                nxt_v = brc[0].nodes;
            }else if(res == 2){
                nxt_v = brc[1].nodes;
            }else {
                if(brc.size() == 3) nxt_v = brc[2].nodes;
                nxt_v.pb(c);
            }
            for(int x: nxt_v) vis[x] = 1;
            v = nxt_v;
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