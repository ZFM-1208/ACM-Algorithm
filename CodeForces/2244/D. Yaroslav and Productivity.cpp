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
void solve1(){
    int n,m; cin >> n >> m;
    vii a(n+1),b(m+1);
    rep(i,1,n) cin >> a[i];
    rep(i,1,m) cin >> b[i];
    sort(b.begin()+1,b.end());
    vii pre(n+1);
    rep(i,1,n) pre[i] = pre[i-1] + a[i];
    int ans = 0;
    int lst = 0;
    for(int i = 1; i <= m; i++){
        ans += abs(pre[b[i]] - pre[lst]);
        lst = b[i];
    }
    ans += pre[n] - pre[lst];
    cout << ans << endl;
}
void solve(){
    int n,m; cin >> n >> m;
    vii a(n+1), b(m+1);
    rep(i,1,n) cin >> a[i];
    rep(i,1,m) cin >> b[i];
    sort(b.begin()+1, b.end(),[](int x, int y){
        return x > y;
    });
    vii pre(n+1);
    rep(i,1,n) pre[i] = pre[i-1] + a[i];
    vector<vii> dp(m+1, vii(2, -inf));
    // dp[i][0]前i个帖子, 选了偶数个帖子的最大价值
    dp[0][0] = 0;
    dp[0][1] = -inf;
    int ans = pre[n];
    for(int i = 1; i <= m; i++){
        // 不选当前帖子
        dp[i][0] = dp[i-1][0];
        dp[i][1] = dp[i-1][1];

        // 选当前帖子
        dp[i][0] = max(dp[i][0], dp[i-1][1] + pre[b[i]]);
        dp[i][1] = max(dp[i][1], dp[i-1][0] - pre[b[i]]);
    }
    cout << ans + 2 * max(dp[m][0], dp[m][1]) << endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve1();
    return 0;
}