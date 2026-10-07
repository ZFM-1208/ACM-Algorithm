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

/*
    1 2 3 4 5
    p
*/
void solve() {
    int n; cin >> n;
    vii a(n+1);
    rep(i,1,n) cin >> a[i];
    vector<int> b(n+1);
    map<int, int> mp;
    for(int x = 1; x <= n - 4; x++){
        b[x] = a[x] + a[x + 2] - a[x + 4];
        mp[b[x]]++;
    }
    int ans = 0;
    for(auto& [_,cn] : mp){
        ans += cn * (cn - 1) / 2;
    }
    for(int x = 1; x <= n - 4; x++){
        int y1 = x+2, y2 = x+4;
        if(x + 2 <= n-4 && b[x] == b[x + 2]){
            ans--;
        }
        if(x + 4 <= n-4 && b[x] == b[x + 4]){
            ans--;
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