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
    int n, k;cin >> n >> k;
    vii a(n+1);
    rep(i, 1, n) cin >> a[i];
    int ans = 0;
    rep(i, 1, n)  if(a[i] == k)  ans++;
    rep(i, 1, n - 1) {
        if(min(a[i], a[i + 1]) < k && k < max(a[i], a[i + 1])){
            ans++;
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