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
struct node {
    int x,y,z;
};
void solve(){
    int n,m,k; 
    cin >> n >> m >> k;
    vii a(n+1);
    vector<node> q(m+1);
    for(int i = 1; i <= m; i++){
        cin >> q[i].x >> q[i].y >> q[i].z;
        a[q[i].x] |= q[i].z;
        a[q[i].y] |= q[i].z;
    }  
    for(int i = 1; i <= m; i++) {
        if((a[q[i].x] & a[q[i].y]) != q[i].z){
            cout << -1 << endl;
            return;
        }
    }
    int ans = 0;
    rep(i, 1, n) ans += a[i];
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