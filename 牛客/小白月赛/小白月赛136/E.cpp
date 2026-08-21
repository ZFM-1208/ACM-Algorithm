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
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
struct State {
    int x, y, r;
};
void solve() {
    int n, m; cin >> n >> m;
    string s; cin >> s;
    vector<string> a(n + 1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        a[i] = " " + a[i]; 
    }
    vector<vector<vii>> dis(n+1,vector<vii>(m+1,vii(3,-1)));
    queue<array<int,3>> q;
    dis[n][m][0] = 0;q.push({n, m, 0});
    dis[n][m][1] = 0;q.push({n, m, 1});
    dis[n][m][2] = 0;q.push({n, m, 2});
    while(!q.empty()){
        auto [x, y, cn] = q.front();
        q.pop();
        int lst = (cn+2) % 3; 
        for(int d = 0; d < 4; d++) {
            for(int k = 1; k <= 3; k++) {
                if(a[x][y] != s[(lst + k - 1) % 3]) continue;
                int nx = x - k * dx[d];
                int ny = y - k * dy[d];
                if(nx >= 1 && nx <= n && ny >= 1 && ny <= m){
                    if(dis[nx][ny][lst] == -1){
                        dis[nx][ny][lst] = dis[x][y][cn] + 1;
                        q.push({nx, ny, lst});
                    }
                }
            }
        }
    }

    rep(i, 1, n) rep(j, 1, m) 
    cout << dis[i][j][0] << " \n"[j==m];
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T = 1;
    if (cin >> T) {
        while (T--) solve();
    }
    return 0;
}