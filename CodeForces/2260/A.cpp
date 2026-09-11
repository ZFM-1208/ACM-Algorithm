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
    int cn = 0;
    vii a(n+1);
    rep(i,1,n){
        cin >> a[i];
        if(a[i] == 0) cn++;
    }
    if(cn < 2){
        cout << -1 << endl;
        return;
    }
    if(a[1] == 0 && a[n] == 0){
        cout << 0 << endl;
        return;
    }
    int ans = 0;
    if(a[1] != 0) ans++;
    if(a[n] != 0) ans++;
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