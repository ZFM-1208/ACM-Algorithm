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
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
void solve(){
    int n,m; cin >> n >> m;
    int a,b; cin >> a >> b;
    vector<string> s(n+1);
    pii st, ed;
    for(int i = 1; i <= n; i++){
        cin >> s[i];
        s[i] = " " + s[i];
        for(int j = 1; j <= m; j++){
            if(s[i][j] == 'S') st = {i,j};
            if(s[i][j] == 'E') ed = {i,j};
        }
    }
    vector<vii> pre(n+1, vii(m+1));
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(s[i][j] == '#'){
                pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + 1LL;
            }else{
                pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
            }
        }
    }
    vector<vii> vis(n+1, vii(m+1));
    vis[st.fi][st.se] = 1;
    queue<pii> q;
    q.push(st);
    while(q.size()){
        auto [x,y] = q.front();
        q.pop();
        if(x == ed.fi && y == ed.se){
            cout << "YES" << endl;
            return;
        }
        for(int i = 0; i < 4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx < 1 || ny < 1 || nx + a - 1 > n || ny + b - 1 > m) continue;
            if(vis[nx][ny]) continue;
            int cnt = pre[nx + a - 1][ny + b - 1] - pre[nx - 1][ny + b - 1] - pre[nx + a - 1][ny - 1] + pre[nx - 1][ny - 1];
            if(cnt == 0){
                vis[nx][ny] = 1;
                q.push({nx, ny});
            }
        }
    }
    cout << "NO" << endl;
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