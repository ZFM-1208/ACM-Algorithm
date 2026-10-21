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
    int n,m; cin >> n >> m;
    vector<vii> a(n+1,vii(m+1));
    rep(i,1,n) rep(j,1,m) cin >> a[i][j];
    int ans = 0;
    for(int j = 1; j <= m; j++){
        int rem = 0;
        for(int i = 1; i <= n; i++){
            rem += a[i][j-1];
            if(a[i][j] >= rem){
                ans += a[i][j] - rem;
                rem = 0;
            }else{
                rem -= a[i][j];
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