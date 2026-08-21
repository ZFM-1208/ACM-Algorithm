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
    int m = 3 * n;
    vector<vii> a(m+1, vii(m+1));
    rep(i,0,m-1) rep(j,0,m-1) cin >> a[i][j];
    int ans = -inf;
    vector<int> dp(1 << m, -inf);
    dp[0] = 0;
    for(int msk = 0; msk < (1LL << m) - 1; msk++){
        if(dp[msk] == -inf) continue; 
        int rem = ((1LL << m) - 1) ^ msk;
        vii cun;
        for(int k = 0; k <= m; k++){
            if((rem >> k) & 1){
                cun.pb(k);
            }
        }
        int i = cun[0];
        for(int j = 1; j < cun.size(); j++){
            for(int k = j + 1; k < cun.size(); k++){
                int nmsk = msk | (1LL << i) | (1LL << cun[j]) | (1LL << cun[k]);
                dp[nmsk] = max(dp[nmsk], dp[msk] + a[i][cun[j]] + a[i][cun[k]] + a[cun[j]][cun[k]]);
            }
        }
    }
    cout << dp[(1 << m) - 1] << endl;
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