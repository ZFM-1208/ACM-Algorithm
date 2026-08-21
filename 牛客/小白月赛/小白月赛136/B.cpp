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
    int n, m, x, y, k;cin >> n >> m >> x >> y >> k;
    int ans = inf;
    for(int i = 0; i <= k; i++){
        for(int j = 0; i + j <= k; j++){
            int res1 = 2 * i * x;
            if(n - 3 * i > 0) res1 += (n - 3 * i) * x;
            int res2 = 3 * j * y;
            if(m - 4 * j > 0) res2 += (m - 4 * j) * y;
            ans = min(ans, res1 + res2);
        }
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