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
inline int read() {
    int x = 0; char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
    return x;
}
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
void solve(){
    // int n,m,k,q; cin >> n >> m >> k >> q;
    int n = read(), m = read(), k = read(), q = read();
    // vector<vector<char>> a(n+1, vector<char>(m+1));
    // for(int i = 1; i <= n; i++){
    //     string s; cin >> s;
    //     for(int j = 1; j <= m; j++){
    //         a[i][j] = s[j-1];
    //     }
    // }
    vector<char> a(n*m); // 坐标(i,j)可以映射为 i * m + j
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            char ch = getchar();
            while (ch != '.' && ch != '#') ch = getchar();
            a[i * m + j] = ch;
        }
    }
    auto get_id = [&](int r, int c) {
        return (r - 1) * m + (c - 1);
    };
    vii comp(n*m);
    int cnt = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            int id = get_id(i, j);
            if(a[id] == '.' && comp[id] == 0)
            {
                queue<pii> q;
                q.push({i, j});
                comp[id] = ++cnt;
                while(!q.empty()) 
                {
                    auto [x, y] = q.front();
                    q.pop();
                    for(int d = 0; d < 4; d++){
                        int nx = x + dx[d], ny = y + dy[d];
                        if(nx >= 1 && nx <= n && ny >= 1 && ny <= m){
                            int nid = get_id(nx, ny);
                            if(a[nid] == '.' && comp[nid] == 0){
                                comp[nid] = cnt;
                                q.push({nx, ny});
                            }
                        }
                    }
                }
            }
        }
    }


    // map<pii,vector<pii>> mp;
    // for(int i = 1; i <= k; i++){
    //     int x1,y1,x2,y2; cin >> x1 >> y1 >> x2 >> y2;
    //     mp[{x1,y1}].push_back({x2,y2});
    // }

    vector<pii> chuansong;
    vii cun;
    for(int i = 0; i < k; i++){
        int x1 = read(), y1 = read(), x2 = read(), y2 = read();
        int u = comp[get_id(x1, y1)];
        int v = comp[get_id(x2, y2)];
        chuansong.pb({u, v});
        cun.pb(u);
        cun.pb(v);
    }
    sort(cun.begin(), cun.end());
    cun.erase(unique(cun.begin(), cun.end()), cun.end());
    int cnt1 = cun.size();
    vii mp(cnt + 1, -1);
    for(int i = 0; i < cnt1; i++){
        mp[cun[i]] = i;
    }
    vector<vii> vis(cnt1,vii(cnt1));
    vector<vii> adj(cnt1);
    for(auto& [u, v] : chuansong){
        int ku = mp[u];
        int kv = mp[v];
        adj[ku].pb(kv);
    }

    for(int i = 0; i < cnt1; i++){
        vis[i][i] = 1;
        queue<int> q;
        q.push(i);
        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(int v : adj[u]){
                if(!vis[i][v]) {
                    vis[i][v] = 1;
                    q.push(v);
                }
            }
        }
    }

    while(q--){
        // int x1,y1,x2,y2; cin >> x1 >> y1 >> x2 >> y2;
        int x1 = read(), y1 = read(), x2 = read(), y2 = read();
        int u = comp[get_id(x1, y1)];
        int v = comp[get_id(x2, y2)];
        if(u == v){
            cout << 1 << endl;
            continue;
        }
        int ku = mp[u];
        int kv = mp[v];
        if(ku != -1 && kv != -1 && vis[ku][kv] == 1){
            cout << 1 << endl;
        }else{
            cout << 0 << endl;
        }
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    // int T = 1; cin >> T;
    int T = read();
    while(T--)
        solve();
    return 0;
}