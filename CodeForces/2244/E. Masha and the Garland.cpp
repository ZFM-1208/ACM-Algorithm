#include<bits/stdc++.h>
using namespace std;
#define rep(i, l, r) for(int i = l; i <= r; i++)
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
    int n,q; cin >> n >> q;
    string s; cin >> s;
    vector<int> d(n+1), pre1(n+1), pre2(n+1);
    for(int i = 1; i <= n; i++) d[i] = (s[i-1]-'0') ^ ((i-1) & 1);
    for(int i = 2; i <= n; i++){
        pre1[i] = pre1[i-1] + (!d[i-1] && d[i]);
        pre2[i] = pre2[i-1] + (d[i-1] && !d[i]);
        // cout << pre1[i] << " " << pre2[i] << endl;
    }
    while(q--){
        int l,r,k; cin >> l >> r >> k;
        int a = d[l] + pre1[r] - pre1[l];
        int b = (!d[l]) + pre2[r] - pre2[l];
        cout << (min(a,b) <= k ? "YES" : "NO") << endl;
    }
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