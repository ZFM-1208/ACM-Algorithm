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
const int N = 1e6, mod = 1e9+7, inf = 1e18+5;
void solve(){
    int n; cin >> n;
    vii a(n+1), b(n+1),c(n+1), d(n+1);
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, n) cin >> b[i];
    rep(i, 1, n) cin >> c[i];
    rep(i, 1, n) cin >> d[i];
    map<pii, int> mp;
    for(int i = 1; i <= n; i++) {
        if(a[i] < b[i]){
            mp[{min(a[i], b[i]), max(a[i], b[i])}] = 0;
        }else{
            mp[{min(a[i], b[i]), max(a[i], b[i])}] = 1;
        }
    }

    bool ok = 1;
    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        if(!mp.count({min(c[i], d[i]), max(c[i], d[i])})){
            ok = 0;
            break;
        }
        if(c[i] < d[i] && mp[{min(c[i], d[i]), max(c[i], d[i])}] == 1) cnt++;
        if(c[i] > d[i] && mp[{min(c[i], d[i]), max(c[i], d[i])}] == 0) cnt++;
    }
    if(ok && cnt % 2 == 0) cout << "Yes" << endl;
    else cout << "No" << endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();
    return 0;
}