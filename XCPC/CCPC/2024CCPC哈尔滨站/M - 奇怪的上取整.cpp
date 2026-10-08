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
    vii cun;
    for(int i = 2; i * i <= n; i++){
        if(n % i == 0){
            cun.pb(i);
            if(i * i != n){
                cun.pb(n / i);
            }
        }
    }
    cun.pb(n);
    sort(cun.begin(), cun.end());
    int ans = 0;
    int ls = 1;
    for(int i = 0; i < cun.size(); i++){
        // cout << cun[i] << endl;
        ans += (n / ls) * (cun[i] - ls);
        ls = cun[i];
    }
    cout << ans + 1 << endl;
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