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
    vii r(m + 1), c(m + 1);
    rep(i, 1, m) cin >> r[i] >> c[i];
    vector<int> vr(n+1),vc(n+1);
    int ans = 0;
    for(int i = m; i >= 1; i--){
        if(!vr[r[i]] && !vc[c[i]]){
            ans++;
        }
        vr[r[i]] = 1;
        vc[c[i]] = 1;
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