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
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
void solve(){
    int n, m, k;cin >> n >> m >> k;
    vector<string> s(n + 1);
    for(int i = 1; i <= n; i++){
        cin >> s[i];
        s[i] = " " + s[i];
    }
    
    vector<int> visr(n+1), visc(m+1);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++) {
            if(s[i][j] == '#'){
                visr[i] = 1;
                visc[j] = 1;
            }
        }
    }
    vector<vii> dist(n+1,vii(m+1,-1));
    queue<pii> q;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++) {
            if (s[i][j] == '.' && !visr[i] && !visc[j]) {
                dist[i][j] = 0;
                q.push({i, j});
            }
        }
    }
    
    int ans = 0;
    while(!q.empty()){
        auto [x, y] = q.front();
        q.pop();
        int d = dist[x][y];
        if(dist[x][y] <= k) ans++;
        if (dist[x][y] == k) continue;
        for(int i = 0; i < 4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx >= 1 && nx <= n && ny >= 1 && ny <= m && s[nx][ny] == '.'){
                if (dist[nx][ny] == -1) {
                    dist[nx][ny] = d + 1;
                    q.push({nx, ny});
                }
            }
        }
    }
    
    cout << ans << endl;
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