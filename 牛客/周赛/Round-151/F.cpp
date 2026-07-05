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
    vector<int> a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    int q; cin >> q;
    while(q--){
        int k; cin >> k;
        int mx = 0;
        int ans = 0;
        for(int x = 0; x < (1LL << n); x++){
            int tp = x;
            int res = 0;
            while(tp){
                if(tp & 1) res++;
                tp >>= 1;
            }
            if(res != k) continue;
            int g = 0;
            for(int i = 1; i <= n; i++){
                if(x >> (i - 1) & 1){
                    if(g == 0) g = a[i];
                    else g = __gcd(g, a[i]);
                }
            }
            if(g > mx){
                mx = g;
                ans = 1;
            }else if(g == mx){
                ans++;
                ans %= mod;
            }
        }
        cout << ans % mod << endl;
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