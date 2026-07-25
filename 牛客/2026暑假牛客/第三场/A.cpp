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
    cnt[k][u][v]: 第k位为 u 且 第k+1位为 v 的个数

*/
void solve(){
    int n; cin >> n;
    vector<vector<vii> > cnt(35,vector<vii>(2,vii(2)));
    for(int i = 1; i <= n; i++){
        int x; cin >> x;
        for(int k = 0; k <= 32; k++){
            cnt[k][((x >> k) & 1)][((x >> (k+1)) & 1)]++;
        }
    }
    int m; cin >> m;
    while(m--){
        int op, x; cin >> op >> x;
        for(int k = 0; k <= 30; k++)
        {
            vector<vii> tp(2,vii(2));
            int xu = (x >> k) & 1;
            int xv = (x >> (k + 1)) & 1;
            for(int u = 0; u < 2; u++)
            {
                for(int v = 0; v < 2; v++)
                {
                    int nu, nv;
                    if(op == 1) nu = xu & u, nv = xv & v;
                    if(op == 2) nu = xu | u, nv = xv | v;
                    if(op == 3) nu = xu ^ u, nv = xv ^ v;
                    tp[nu][nv] += cnt[k][u][v];
                }
            }
            for(int u = 0; u < 2; u++)
            {
                for(int v = 0; v < 2; v++)
                {
                    cnt[k][u][v] = tp[u][v];
                }
            }
        }
        int ans = 0;
        for(int k = 0; k <= 30; k++)
        {
            ans += cnt[k][1][0];
        }
        cout << ans << endl;
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