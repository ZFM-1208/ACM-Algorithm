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

void solve() {
    int n, x; cin >> n >> x;
    vii a(n + 1);
    rep(i, 1, n) cin >> a[i];
    int l = 1, r = 1e9 + 7;
    int ans = r;
    auto check =[&](int k) -> int {
        vii vis(n+1);
        int cnt = 0;
        for(int i = 1; i <= n; i++){
            int ok1 = 0, ok2 = 0;
            if(i-1 >= 1 && a[i] - a[i-1] <= k) ok1 = 1;
            if(i+1 <= n && a[i+1] - a[i] <= k) ok2 = 1;
            if(ok1 == 0 && ok2 == 0){
                vis[i] = 1;
                cnt++;
            }
        }
        /*
            1 2 3 4 5 6 7 8 9 10
            p                  p

            k = 4
            1 2 3 4 5 6 7 8 9 10 
            p       o        o p            
        */
        for(int i = 1; i <= n; i++){
            if(i+1 <= n && vis[i] && vis[i+1]){
                if(a[i+1] - a[i] <= 2*k) {
                    i++;
                    cnt--;
                }
            }
        }
        return cnt <= x;
    };


    while (l <= r) {
        int mid = l + (r - l) / 2;
        if(check(mid)){
            ans = mid;
            r = mid - 1; 
        } else {
            l = mid + 1;
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