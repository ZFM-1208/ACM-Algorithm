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
/*
    1. 数字很长，存不下
    2. 取模会破坏大小关系
    ==> 登长数字比较 == 字典序(前缀+当前位)
    对图进行分层, 同一层 ly[d+1] 的所有点，从起点走过来的路径长度是严格相等的
    一个长度为 d+1 的数字串，本质上是由两部分组成的
    前 d 位的数字串 和 最后一位数字c

    * 把超长字符串的比较，降维成两个数字的比较！
    如果我们已经知道了第 d 层所有点的相对大小排名
    那么到达第 d+1 层某个点 v 的这个大整数，其大小完全由一个二元组唯一决定：
    {二元组} = ({前缀的排名}, {最后这一个数字}) = (x[u], c)
    第一关键字比较前缀谁更小（x[u] 越小越好）
    若前缀一样小（x[u] 相同），再看最后这一位数字谁更小（c 越小越好）

    位数少的一定比位数多的小 ==> 转化为必须走边数最少的最短路。
    长度相等的数字比大小 ==> 等价于字典序比较
    数字太大不能存 ==> 只能按层推进，自前向后贪心

*/
struct Edge{
    int to, v;
};
void solve(){
    int n,m; cin >> n >> m;
    vector<vector<Edge>> adj(n+1);
    for(int i = 1; i <= m; i++){
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].pb({v, c});
    } 
    vii dist(n + 1, -1);
    queue<int> q;
    dist[1] = 0;
    q.push(1);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(auto& [v,_] : adj[u]) {
            if(dist[v] == -1){
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    int md = 0;
    rep(i,1,n) md = max(md, dist[i]);
    vector<vii> ly(md+1);
    for(int i = 1; i <= n; i++){
        ly[dist[i]].pb(i);
    }
    vii ans(n+1);
    vii x(n + 1, 0);// 第 d 层的点 u 的排名,值越小，代表从起点到 u 拼出的数字越小）
    vector<pii> nb(n + 1, {inf, inf});// 在所有入边中挑选出字典序最小的那个组合，保存在 nb[v] 里
    vii bst(n + 1, 0);// 记下这个最优解来自哪个前驱 $u$
    x[1] = 0;
    ans[1] = 0;
    for(int d = 0; d <= md-1; d++){
        // 寻找每个点 v 的“最优入边”
        for(int u : ly[d])
        {
            for(auto& [v,c]: adj[u]){
                if(dist[v] == d+1){
                    pii cur = {x[u], c}; // 前缀排名 + 当前位数字
                    if(cur < nb[v]){ // pair 自带双关键字比大小
                        nb[v] = cur; // 记录 v 能拿到的最小数值二元组
                        bst[v] = u;  // 记录这个最优值是从哪个前驱 u 转移过来的
                    }
                }
            }
        }
        // 对第 d+1 层进行同层排序
        sort(ly[d + 1].begin(), ly[d + 1].end(), [&](int a, int b) {
            return nb[a] < nb[b];// 比较谁的二元组更小
        });
        int rk = 0;
        /*
            为什么要算 rk 并赋值给 x？
            因为第 d+1 层的点接下来要作为前驱，去更新第 d+2 层的点！
            下一层需要用到这里的 x 作为它们的前缀排名。
            如果两个点的 nb 一模一样（比如拼出的数字都是 135），它们并列第一，获得相同的 rk。
            为什么可以算 ans 了？
            一旦路径敲定，真实答案就可以自然地通过递推公式 (ans[前驱] * 10 + c) % mod 顺利算出。
        */
        for(int i = 0; i < ly[d+1].size(); i++){
            // 如果跟前一个点的二元组不同，排名就必须后移
            if(i && nb[ly[d+1][i]] != nb[ly[d+1][i-1]]){
                rk++;
            }
            x[ly[d+1][i]] = rk; // 赋予第 d+1 层新的相对排名 x
            // 此时已经完全确定最优前驱了，放心地边走边模
            ans[ly[d+1][i]] = (ans[bst[ly[d+1][i]]] * 10 + nb[ly[d+1][i]].se) % mod;
        }
    }
    for(int i = 2; i <= n; i++) cout << ans[i] << endl;
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