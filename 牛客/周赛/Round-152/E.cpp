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
    vii a(n+1), b(n+1);
    rep(i,1,n) cin >> a[i];
    rep(i,1,n) cin >> b[i];
    vector<vii> dp(n+1,vii(2, -inf));
    dp[0][0]=0;
    for(int i = 1; i <= n; i++){
        if(a[i] <= 0){
            dp[i][0] = max(dp[i-1][0], dp[i-1][1]);
        }else{
            dp[i][0] = max(dp[i-1][0] + (b[i] / 2) * a[i], dp[i-1][1] + (b[i]-1) / 2 * a[i]);
            dp[i][1] = max(dp[i-1][0] + ((b[i] + 1) / 2) * a[i], dp[i-1][1] + (b[i]) / 2 * a[i]);
        }
    }
    int ans = max(dp[n][0], dp[n][1]);
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