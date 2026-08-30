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
    int m, q, b;cin >> m >> q >> b;
    vii a(m+1), pre(m+1);
    rep(i, 1, m) {
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
    }
    while(q--){
        int p; cin >> p;
        int k = lower_bound(pre.begin() + 1, pre.end(), p) - pre.begin();
        int s1;
        if(k&1) s1 = b;
        else s1 = 1-b;
        cout << s1 << " " << k << " " << p - pre[k - 1] << endl;
    }
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