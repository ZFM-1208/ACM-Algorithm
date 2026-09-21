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
const int N = 2e5+100, mod = 1e9+7, inf = 1e18 + 5;
vii su;
int vis[N];
void init(){
    for(int i = 2; i < N; i++){
        if(vis[i] == 0){
            su.pb(i);
            for(int j = i * i; j < N; j += i){
                vis[j] = 1;
            }
        }
    }
}
void solve(){
    int n,k; cin >> n >> k;
    vii a(n+1);
    rep(i,1,n) cin >> a[i];
    int ans = 0;
    vii dp(n+1, inf);
    for(int x = 1; x <= n; x++){
        if(x <= k) {dp[x] = 0; continue;}
        int tp = x;
        for(int p : su){
            if(p * p > tp) break;
            if(tp % p == 0){
                dp[x] = min(dp[x], 1 + p * dp[x/p]);
                while(tp % p == 0){
                    tp /= p;
                }
            }
        }
        if(tp > 1 || vis[tp] == 0){
            dp[x] = min(dp[x], 1 + tp * dp[x/tp]);
        }
    }
    for(int i = 1; i <= n; i++){
        if(a[i] > k){
            ans += dp[a[i]];
        }
    }
    cout << ans << endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T = 1;
    init();
    cin >> T;
    while(T--)
        solve();
    return 0;
}