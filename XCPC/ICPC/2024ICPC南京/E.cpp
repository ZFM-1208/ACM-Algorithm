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
    int n,k; cin >> n >> k;
    string s; cin >> s;
    int ans = 0;
    string op;
    for(int q = 0; q <= min({n-1,k,6LL}); q++){
        if(q != 0) op += s[q-1];
        string tp = s.substr(q);
        if(q != 0) tp = tp + op;
        int cnt = 0;
        for(int i = 0; i < n; i++){
            if(i + 7 <= n && tp.substr(i,7) == "nanjing"){
                cnt++;
            }
        }
        ans = max(ans, cnt);
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