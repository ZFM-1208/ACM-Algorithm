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
    map<int, pii> mp;
    for(int i = 1; i <= n; i++){ 
        int x; cin >> x;
        if(!mp.count(x)) {
            mp[x] = {i, i};
        } else {
            mp[x].se = i;
        }
    }
    int ans = 0;
    for (auto& [_, p] : mp) {
        auto [l,r] = p;
        if (l < r && (r - l) % 2 == 0)  ans++; 
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