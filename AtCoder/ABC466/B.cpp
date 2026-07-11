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
    int n,m; cin >> n >> m;
    map<int,int> mp;
    for(int i = 1; i <= n; i++){
        int x,y; cin >> x >> y;
        mp[x] = max(mp[x], y);
    }
    for(int i = 1; i <= m; i++){
        if(mp.count(i)){
            cout << mp[i] << " ";
        }else{
            cout << -1 << " ";
        }
    }
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