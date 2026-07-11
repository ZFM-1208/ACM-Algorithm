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
    int n,k; cin >> n >> k;
    vii a(n+1),b(n+1);
    rep(i,1,n) cin >> a[i] >> b[i];
    vector<vector<vii>> dp(n+1, vector<vii>(k+1,vii(2, -inf)));
    dp[0][0][0] = 0;
    int ans = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= k; j++){
            // 第i: 正面
            if(dp[i-1][j][0] != -inf){
                dp[i][j][0] = max(dp[i][j][0], dp[i-1][j][0] + a[i]);
            }
            if(dp[i-1][j][1] != -inf){
                dp[i][j][0] = max(dp[i][j][0], dp[i-1][j][1] + a[i]);
            }
            // 第i: 反面
            if(dp[i-1][j][1] != -inf){
                dp[i][j][1] = max(dp[i][j][1], dp[i-1][j][1] + b[i]);
            }
            if(j > 0 && dp[i-1][j-1][0] != -inf){
                dp[i][j][1] = max(dp[i][j][1], dp[i-1][j-1][0] + b[i]);
            }
        }
    }
    for(int i = 0; i <= k; i++){
        ans = max({ans, dp[n][i][0], dp[n][i][1]});
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