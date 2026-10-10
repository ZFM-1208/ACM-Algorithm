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
    // vii a(n+1),pre(n+1);
    // map<int,int> cnt;
    // int k;
    // for(int i = 1; i <= k; i++){
    //     cin >> a[i];
    //     // cnt[a[i]]++;
    //     pre[i] = pre[i-1] ^ a[i];
    //     // cnt[pre[i]]++;
    // }
    // for(int i = 0; i <= k; i++){
    //     cnt[pre[i]]++;
    // }
    // int ans = 0;
    // int cc = 0;
    // for(auto [x,cn]: cnt){
    //     cc += cc;
    //     ans += (cn - 1) * cn / 2;
    // }
    // cc--;
    // int mx = cc - ans;
    // cout << "mx: " << mx << endl;

    int mx = 0;
    for(int i = 20; ; i--){
        if((n >> i) & 1){
            mx = i;
            break;
        }
    }
    /*
        3 = 2^2 - 1
        7 = 2^3 - 1
    */
    int ans1 = (1 << (mx+2)) - 1;
    cout << ans1 << endl;
    // ai <= 2^(mx+1)

    /*
             0123456789..
        pre: aabbccddeeffgg
        a[i] = pre[i] ^ pre[i-1]
        a:   0 x 0 y 0 z ...
    */
    vii pre(ans1 + 1);
    
    /*
        0 1 0
        pre: 0 0 1 1
        0 1 0 2 0 1 0
        pre: 0 0 1 1 3 3 2 2
        0 1 0 2 0 1 0 4 0 1 0 2 0 1 0
        pre: 0 0 1 1 3 3 2 2 6 6 7 7 5 5 4 4
        0, 1, 0, 2, 0, 1, 0, 4, 0, 1, 0, 2, 0, 1, 0, 8, 0, 1, 0, 2, 0, 1, 0, 4, 0, 1, 0, 2, 0, 1, 0
        pre: 
    */
    vii a = {0, 1, 0};
    for (int i = 1; i <= mx; i++) {
        int sz = a.size();
        a.pb(1LL << i); 
        for(int j = 0; j < sz; j++){
            a.pb(a[j]); 
        }
    }
    for(int x: a){
        cout << x << " ";
    }
    cout << endl;
    

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