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
int fx[] = {1,-1,0,0};
int fy[] = {0,0,1,-1};
// 必胜态： 相邻格子有比他还高且必输
void solve(){
    int n,m; cin >> n >> m;
    vector<vii> a(n+1,vii(m+1));
    vector<array<int,3>> cun;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> a[i][j];
            cun.push_back({a[i][j], i, j});
        }
    }
    sort(cun.begin(), cun.end(),[](auto x, auto y){
        return x[0] > y[0];
    });
    vector<vii> vis(n+1,vii(m+1));
    for(auto [d,x,y]: cun){
        for(int i = 0; i < 4; i++){
            int nx = x + fx[i];
            int ny = y + fy[i];
            if(nx < 1 || ny < 1 || nx > n || ny > m) continue;
            if(a[nx][ny] > d && vis[nx][ny] == 0) {
                vis[x][y] = 1;
            }
        }
    }
    int q; cin >> q;
    while(q--){
        int x, y; cin >> x >> y;
        cout << (vis[x][y] == 1 ? "First" : "Second") << endl;
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