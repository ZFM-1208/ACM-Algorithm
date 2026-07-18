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
    int n,m,k; cin >> n >> m >> k;
    vii a(n+1), b(m+1);
    rep(i,1,n) cin >> a[i];
    vector<pii> mp;
    for(int i = 1; i <= m; i++){
        cin >> b[i];
        mp.pb({b[i], i});
    }
    sort(mp.begin(), mp.end());
    vii res;
    for(int i = 1; i <= n; i++){
        int pos = a[i] ^ ((1LL << k) - 1);
        auto it = lower_bound(mp.begin(), mp.end(), make_pair(pos, 0LL));
        if(it != mp.end() && it->first == pos){
            res.pb(it->second);
        }
    }
    vector<int> dp;
    for(auto &x: res){
        auto it = lower_bound(dp.begin(), dp.end(), x);
        if(it != dp.end()) {
            *it = x;
        }else dp.pb(x);
    }
    cout << dp.size() << endl;

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