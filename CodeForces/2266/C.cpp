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
    string s; cin >> s;
    s = " " + s;
    vii pre(n+2), suf(n+2);
    for(int i = 1; i <= n; i++){
        pre[i] = pre[i - 1] + (s[i] == '1');
    }
    for(int i = n; i >= 1; i--){
        suf[i] = suf[i + 1] + (s[i] == '0');
    }
    int ans = inf;
    for(int i = 0; i <= n; i++){
        int res = pre[i] + suf[i + 1];
        ans = min(ans, res);
    }
    if(s[1] == '1') ans = suf[1];
    cout << ans << endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();
    return 0;
}