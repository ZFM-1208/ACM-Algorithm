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
double pi = acos(-1);
const int N = 5e5, mod = 1e9 + 7, inf = 1e18 + 5;
struct node{
    int x;
    int t;
    int id;
};
/*
    我们把这些人的出现时间t += 到根节点的时间
    这样就知道每个人到根节点1的准确时间。

    不难想到 :
        1.同一批到根节点的人才可能发生碰撞
        2.所有的碰撞，必定发生在其路径交汇的祖先节点处
    check :
        1.若某个节点汇聚了>= 2 个人：所有人同归于尽，无法继续向上走
        2.若某个节点只有 1 个人到达/出发：该幸存者继续沿着向上的路径走向上方的下一个交汇点
        3.若该幸存者一路没有遇到任何人，最终到达根节点 1，则成功逃脱
    虚树加速 :
        1. 组内只有部分节点有人出发，如果遍历整棵大树会导致 O(n * m) 超时
        2. 我们只需要提取当前组的起点集合 + 根节点 1 + 相邻起点的两两 LCA
           就能在 O(k log k) 时间内把这些关键点浓缩成一棵虚树
        3. 在虚树中，我们用单调栈确定每个关键点的直属虚树父亲 dad[u]
    逆 DFN 序自底向上合并 :
        1. DFN 序较大的节点深度较深，逆 DFN 序天然是自底向上的拓扑排序
        2. 倒序遍历虚树点集
            <1>: 若当前节点 u 的人数 cnt[u] == 1
                (1): 若 u = 1：到达根节点，逃脱成功，记录答案
                (2): 若 u != 1：该幸存者向上走到虚树父亲 p = dad[u], 令 cnt[p]++，并传递人员编号
            <2>: 若 cnt[u] >= 2：发生碰撞，所有人消失，不向上传递
        3. 遍历结束后，将虚树涉及的节点数据重置为 0，复杂度与本组人数线性相关
*/
void solve(){
    int n,m; cin >> n >> m;
    vector<vii> adj(n+1); 
    for(int i = 1; i < n; i++){
        int u, v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vector<int> ans(m+1);
    vii dep(n+1), dfn(n+1), out(n+1); // 深度、进入时间戳、离开时间戳
    vector<vii> fa(n+1, vii(25)); 
    int ti = 0; // DFS 时间戳计数器
    auto dfs_lca = [&](auto& self, int u, int p) -> void {
        dfn[u] = ++ti; // 记录进入节点的时间戳
        dep[u] = dep[p] + 1;
        fa[u][0] = p;
        for(int i = 1; i <= 20; i++){
            fa[u][i] = fa[fa[u][i-1]][i-1];
        }
        for(int v: adj[u]){
            if(v == p) continue;
            self(self, v, u);
        }
        out[u] = ti; // 记录离开子树的时间戳
    };
    dfs_lca(dfs_lca, 1, 0);
    auto get_lca = [&](int u, int v) -> int {
        if(dep[u] < dep[v])swap(u, v);
        for(int i = 20; i >= 0; i--){
            if(dep[fa[u][i]] >= dep[v]){
                u = fa[u][i];
            }
        }
        if(u == v) return u;
        for(int i = 20; i >= 0; i--){
            if (fa[u][i] != fa[v][i]){
                u = fa[u][i];
                v = fa[v][i];
            }
        }
        return fa[u][0];
    };
    
    vector<node> a(m+1);
    for(int i = 1; i <= m; i++){
        cin >> a[i].x >> a[i].t;
        a[i].t += dep[a[i].x];
        a[i].id = i;
    }
    sort(a.begin()+1, a.end(),[&](auto x, auto y){
        return x.t < y.t;
    });
    vector<int> mp(n + 1);                    // mp[u]: 记录到达节点 u 的幸存者人员编号
    vector<int> dad(n + 1);                   // dad[u]: 虚树上节点 u 的父节点
    vector<int> cnt(n + 1);                   // cnt[u]: 当前到达节点 u 的人数
    int l = 1, r = 1;
    while(l <= m){
        while(r <= m && a[r].t == a[l].t) r++;
        // 同一时刻到达的合法区间 : [l, r)
        vector<int> cl; 
        cl.pb(1); // 根节点 1 是逃脱终点，必须加入虚树
        for(int i = l; i < r; i++){
            cl.pb(a[i].x);        // 所有人起点加入虚树
            cnt[a[i].x]++;        // 统计起点初始人数
            mp[a[i].x] = a[i].id; // 记录该处的人员编号
        }      
        // 关键点按 DFN 序排序并去重
        sort(cl.begin(),cl.end(),[&](auto x, auto y){
            return dfn[x] < dfn[y];
        });
        cl.erase(unique(cl.begin(), cl.end()), cl.end());       
        // 将相邻点的 LCA 加入点集（虚树的核心交汇点）
        int k = cl.size();
        for(int i = 0; i < k - 1; i++){
            int lca = get_lca(cl[i], cl[i+1]);
            cl.push_back(lca);
        }
        // 再次按 DFN 序排序并去重，得到完整的虚树点集
        sort(cl.begin(),cl.end(),[&](auto x, auto y){
            return dfn[x] < dfn[y];
        });
        cl.erase(unique(cl.begin(), cl.end()), cl.end());
        // 单调栈构建虚树的有向父子关系
        stack<int> st;
        for(int i = 0; i < cl.size(); i++){
            int u = cl[i];
            // 若栈顶节点的子树不包含 u，则栈顶节点出栈; 找 -> 栈顶元素.out >= u.out
            while(st.size() && out[st.top()] < out[u]){
                st.pop();
            }
            if(!st.empty()){
                dad[u] = st.top(); // 栈顶即为 u 在虚树上的直属父亲(原来树上离开子树的时间戳 >= u)
            }
            st.push(u);
        }

        for(int i = cl.size() - 1; i >= 0; i--){
            int u = cl[i];
            if(u == 1 && cnt[u] == 1) ans[mp[u]] = 1;
            else if(cnt[u] == 1){
                int p = dad[u];
                cnt[p]++;
                mp[p] = mp[u];        
            }else if(cnt[u] >= 2){
                ans[mp[u]] = 0;
            }
            cnt[u] = 0;
            mp[u] = 0;
            dad[u] = 0;
        }
        l = r;
    }
    rep(i,1,m) cout << ans[i];
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}