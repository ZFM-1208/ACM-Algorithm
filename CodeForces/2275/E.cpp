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
    vii a(n + 1), b(n + 1);
    rep(i,1,n) cin >> a[i];
    rep(i,1,n) cin >> b[i];
    vii d(n+1,1); // ai <-> bi
    vii d1(n+1,1); // bi <-> a[i+1]
    vii d2(n+1,1); // ai <-> b[i+1]
    for(int i = 1; i <= n; i++){
        if(a[i] == b[i]) d[i]++;
        if(i < n){
            if(a[i] == b[i+1]) d2[i]++;
            if(b[i] == a[i+1]) d1[i]++;
        }
    }
    vector<int> pre(n+1);
    for(int i = 2; i <= n; i++){
        pre[i] = pre[i-1] + d[i-1] + d1[i-1];
    }
    vector<int> suf(n+1);
    for(int i = n-1; i >= 1; i--){
        suf[i] = suf[i+1] + d1[i] + d2[i];
    }
    int ans = 0;
    for(int i = 1; i <= n; i++){
        ans = max(ans, pre[i] + suf[i] + d[n]);
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