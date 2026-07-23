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
    int n; cin >> n;
    vii a(n+2);
    rep(i,1,n) cin >> a[i];
    int ans = 0;
    vector<vii> dp(n+1,vii(2, inf));
    // dp[i][0]: 前i项贡献，且i比i+1先删除
    // dp[i][1]: 前i项贡献，且i+1比i先删除
    dp[0][0] = 0;
    for(int i = 1; i <= n; i++){
        dp[i][0] = min(dp[i - 1][0] + a[i + 1], dp[i - 1][1] + max(a[i - 1], a[i + 1]));
        dp[i][1] = min(dp[i - 1][0], dp[i - 1][1] + a[i - 1]);
    }
    cout << min(dp[n][0], dp[n][1]) << endl;
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