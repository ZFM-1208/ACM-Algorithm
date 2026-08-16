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
    int n, k; cin >> n >> k;
    vii a(n+1);
    rep(i,1,n) cin >> a[i];
    int ans = 1,sum = 0;
    int l = 1, r = 1;
    while(r <= n){
        if(r != 1) sum += abs(a[r] - a[r - 1]);
        while(sum > k && l < r){
            sum -= abs(a[l + 1] - a[l]);
            l++;
        }
        ans = max(ans, r - l + 1);
        r++;
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