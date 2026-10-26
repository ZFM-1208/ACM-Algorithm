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
    vii a(n+1);
    rep(i,1,n) cin >> a[i];
    auto get =[&]() -> int {
        vii vis(n+2),f(n+1);
        int mx = 0;
        for(int i = 1; i <= n; i++){
            vis[a[i]] = 1;
            while(vis[mx]) mx++;
            f[i] = mx;
        }
        sort(f.begin()+1,f.end(),greater<int>());
        return f[k];
    };
    int re = get();
    int res = re;
    pii ans = {-1,-1};
    for(int i = 1; i <= n; i++) {
        for(int j = i+1; j <= n; j++){
            swap(a[i], a[j]);
            int cur = get();
            if(cur > res){
                res = cur;
                ans = {i,j};
            }
            swap(a[i], a[j]); 
        }
    }
    if(res > re) {
        cout << ans.fi << " " << ans.se << endl;
    } else {
        cout << -1 << endl;
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