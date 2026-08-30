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
    int x; cin >> x;
    if(x == 0){
        cout << 0 << " " << -1 << " " << -1 << endl;
        return;
    }
    int cnt = 0;
    int mn = -1, mx = -1;
    for(int i = 0; i <= 62; i++){
        if((x >> i) & 1){
            cnt++;
            if(mn == -1) mn = i;
            mx = i;
        }
    }
    cout << cnt << " " << mn << " " << mx << endl;
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