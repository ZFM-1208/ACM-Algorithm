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
    int n,l,W;
    cin >> n >> l >> W;
    vector<int> x(n+1),w(n+1);
    __int128 sum = 0, sum1 = 0;
    for(int i = 1; i <= n; i++){
        cin >> x[i] >> w[i];
        sum += w[i];
        sum1 += w[i] * x[i];
    }
    int ans = 0;
    for(int i = 1; i <= n; i++){
        __int128  s1 = sum - w[i];
        __int128  s2 = sum1 - w[i] * x[i];
        __int128  ss1 = 2 * s2 + W * l;
        __int128  ss2 = 2 * (s1 + W);
        if(ss1 % ss2 == 0){
            if(0LL <= ss1 / ss2 && ss1 / ss2 <= l){
                ans++;
            }
        }
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