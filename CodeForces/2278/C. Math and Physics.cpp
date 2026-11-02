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
1 2 3 4
2 4 4
4 6
9

2 1 1 1 2
2 1 2
2 2
3
*/
void solve(){
    int n; cin >> n;
    vii a(n+1);
    int sum = 0,mx = 0;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        sum += a[i];
        mx = max(mx, a[i]);
    }
    if(mx == 1){
        cout << -1 << endl;
        return;
    }
    rep(i, 2, n - 1) if(a[i] >= 2){
        cout << sum - 1 << endl;
        return;
    }
    cout << sum - (n - 1) << endl;
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