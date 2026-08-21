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
const int N = 1e6, mod = 998244353, inf = 1e18 + 5;
struct DSU {
    vector<int> fa,siz;
    DSU(int n) {
        fa.resize(n+1);
        siz.resize(n+1);
        iota(fa.begin(), fa.end(), 0);
        for(int i = 0; i <= n; i++) siz[i] = 1;
    }
    int find(int x){
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }
    
    void merge(int x, int y){
        int fx = find(x);
        int fy = find(y);
        if(fx != fy){
            fa[fx] = fy;
            siz[fy] += siz[fx];
        }
    }
};
template<typename T> struct Flow_ {
    const int n;
    const T inf = numeric_limits<T> :: max();
    struct Edge{
        int to;
        T w;
        Edge(int to, T w) : to(to), w(w){}
    };
    vector<Edge> ver;
    vector<vii> h;
    vii cur,d;
    Flow_(int n) :n(n+1),h(n+1){}

    void add(int u, int v, T c){
        h[u].pb(ver.size());
        ver.emplace_back(v,c);
        h[v].pb(ver.size());
        ver.emplace_back(u,0);
    }

    bool bfs(int s, int t){
        d.assign(n,-1);
        d[s] = 0;
        queue<int> q;
        q.push(s);
        while(!q.empty()){
            auto x =  q.front();
            q.pop();
            for(auto it: h[x]){
                auto &[y,w] = ver[it];
                if(w && d[y] == -1){
                    d[y] = d[x] + 1;
                    if(y == t) return true;
                    q.push(y);
                }
            }
        }
        return false;
    }

    T dfs(int u, int t, T f){
        if(u == t) return f;
        auto r = f;
        for(int &i = cur[u]; i < h[u].size(); i++){
            auto j = h[u][i];
            auto &[v,c] = ver[j];
            auto &[u,rc] = ver[j^1];
            if(c && d[v] == d[u] + 1){
                auto a = dfs(v,t,std::min(r,c));
                c -= a;
                rc += a;
                r -= a;
                if(!r) return f;
            }
        }
        return f - r;
    }
    T work(int s, int t){
        T ans = 0;
        while(bfs(s,t)){
            cur.assign(n,0);
            ans += dfs(s,t,inf);
        }
        return ans;
    }
};
using Flow = Flow_<int>;
void solve()
{
    int n,m; cin >> n >> m;
    Flow fl(n);
    vector<vii> edge(n+1,vii(n+1));
    for(int i = 1; i <= m; i++){
        int x,y,w; cin >> x >> y >> w;
        if(x == y) continue;
        fl.add(x,y,w);
        fl.add(y,x,w);
        edge[x][y] += w;
        edge[y][x] += w;
    }
    int MinCut = inf,S = 1,T = 1;
    vii bin(n+1);
    auto contract = [&]() -> int { 
        vii dis(n+1),vis(n+1);
        int Min = 0;
        for(int i = 1; i <= n; i++){
            int k = -1, maxc = -1;
            for(int j = 1; j <= n; j++){
                if(!bin[j] && !vis[j] && dis[j] > maxc){
                    k = j;
                    maxc = dis[j];
                }
            }
            if(k == -1) return Min;
            S = T;
            T = k;
            Min = maxc;
            vis[k] = 1;
            for(int j = 1; j <= n; j++){
                if(!bin[j] && !vis[j]){
                    dis[j] += edge[k][j];
                }
            }
        }
        return Min;
    };
    for(int i = 1; i < n; i++){
        int val = contract();
        bin[T] = 1;
        MinCut = min(MinCut, val);
        if(!MinCut){
            cout << 0 << endl;
            return;
        }
        for(int j = 1; j <= n; j++){
            if(!bin[j]){
                edge[S][j] += edge[j][T];
                edge[j][S] += edge[j][T];
            }
        }
    }
    cout << MinCut * (n-1) << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}