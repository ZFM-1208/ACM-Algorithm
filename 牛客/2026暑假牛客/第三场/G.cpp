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

void solve(){
    int n, m; cin >> n >> m;
    vector<vii> a(n+1,vii(m+1));
    vector<vector<pii>> p(n * m + 1);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> a[i][j];
            p[a[i][j]].pb({i,j});
        }
    }
    for(int i = 1; i <= n*m; i++){
        p[i].pb({n+1,0});
    }
    vector<vii>d(n+2,vii(m+2));;

    auto add = [&](int x1, int y1, int x2, int y2) {
        if(!(1 <= x1 && x1 <= n) || !(1 <= x2 && x2 <= n) || !(1 <= y1 && y1 <= m) || !(1 <= y2 && y2 <= m)) return;
        if(x1 > x2) return;
        if(y1 >= y2) return;
        d[x1][y1]++;
        d[x1][y2 + 1]--;
        d[x2 + 1][y1]--;
        d[x2 + 1][y2 + 1]++;
    };
    for(int i = 1; i <= n*m; i++){
        if(p[i].size() <= 2) continue;
        priority_queue<pii> pq; // 大根堆 {列，行}
        for(auto [x,y]: p[i]) pq.push({y, x});
        int l = m; // 上方点最小列号
        int pre = 0; // 上一段矩形up行
        for(auto [x1,y1]: p[i]){
            if(x1 <= pre) continue;
            if(!pq.empty()){
                auto [y2, x2] = pq.top();
                add(pre, l, x2, y2);
            }
            l = min(l, y1);
            while(!pq.empty() && pq.top().se <= x1) pq.pop();
            pre = x1;
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            d[i][j] += d[i - 1][j] + d[i][j - 1] - d[i - 1][j - 1];
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) 
            cout << (d[i][j] != 0);
        cout << endl;
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