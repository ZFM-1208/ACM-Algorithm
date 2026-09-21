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
/*

    1 2 3 4 5
    a b c d e
    [3,5]
    1 2  3      4     5
    a b (e-2) (c+1) (d+1)
    a-1
    b-2
    e-5
    c-3
    d-4
*/
void solve(){
    int n; cin >> n;
    vii a(n+1);
    rep(i,1,n) cin >> a[i];
    vii b;
    rep(i,1,n) b.pb(a[i] - i);
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    int ans = 0;
    int l = 0, r = 0;
    while(l < b.size()){
        while(r < b.size() && b[r] == b[l] + (r - l)) r++;
        // cout << "l: " << l << " r: " << r << endl;
        ans = max(ans, r - l);
        // cout << "ans: " << ans << endl;
        l = r;
    }
    cout << ans << endl;
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