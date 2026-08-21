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
    0 -3 -8 -15 -24
    3 0 -5 -12 -21
    8 5 0 -7 -16
    15 12 7 0 -9
    24 21 16 9 0

    大<----------------------小
    小0 -3 -8 -15 -24 -35 -48
    | 3 0 -5 -12 -21 -32 -45
    | 8 5 0 -7 -16 -27 -40
    | 15 12 7 0 -9 -20 -33
    | 24 21 16 9 0 -11 -24
    | 35 32 27 20 11 0 -13
    | 48 45 40 33 24 13 0
    大
*/
void solve(){
    int n,m,k; cin >> n >> m >> k;
    // vector<vii> a(n+1,vii(m+1));
    // vii ans;
    // for(int i = 1; i <= n; i++){
    //     for(int j = 1; j <= m; j++){
    //         a[i][j] = i*i-j*j;
    //         ans.pb(a[i][j]);
    //     }
    // }
    // // sort(ans.begin(), ans.end());
    // // for(int x: ans) cout << x << " "; cout << endl;
    // for(int i = 1; i <= n; i++){
    //     for(int j = 1; j <= m; j++){
    //         cout << a[i][j] << " \n"[j==m];
    //     }
    // }
    int l = 1 - m*m, r = n*n - 1;
    int res = -1;
    auto check = [&](int x) -> bool {
        int cnt = 0;
        for(int i = 1; i <= n; i++){
            if(i * i >= x){
                int cn = sqrt(i*i - x);
                cn = min(cn, m);
                cnt += cn;
                if(cnt >= k) return true;
            }
        }
        return cnt >= k;
    };

    while(l <= r){
        int mid = (l + r) >> 1;
        if(check(mid)){
            res = mid;
            l = mid + 1;
        }else{
            r = mid - 1;
        }
    }
    // cout << res << endl;
    int ans = 0;
    int cnt = 0;
    for(int i = 1; i <= n; i++){
        if(i * i >= res){
            int j = sqrt(i*i - res);
            j = min(j,m);
            cnt += j;
            ans += i*i*j - j*(j+1)*(2*j+1)/6;
        }
    }
    if(k - cnt) ans += (k - cnt) * res;
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