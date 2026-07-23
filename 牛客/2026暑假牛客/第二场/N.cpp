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
    vii pre(n+1,0);
    rep(i,1,n) cin >> a[i];
    sort(a.begin()+1,a.end());
    for(int i = 1; i <= n; i++){
        pre[i] = pre[i-1] + a[i];
    }    
    if(k&1){
        int ans = 0;
        // k = 3
        // 1 2 3 4 5 6 7
        // 1 2   p p p  
        for(int i = k/2+1; i <= n - k/2; i++){
            int tp = pre[n] - pre[k/2] - (pre[i+k/2] - pre[i-1]);
            tp += a[i] * k;
            // cout << tp << endl;
            ans = max(ans, tp);

        }
        cout << ans << endl;
    }else{
        // k = 6
        // 1 2 3 4 5 6 7 8 9 10
        // 1 2         p 
        int ans = 0;
        for(int i = k/2; i<= n - k/2; i++){
            int tp = pre[n] - pre[k/2-1] - (pre[i+k/2] - pre[i-1]);
            tp += (a[i] + a[i+1]) * k / 2;
            ans = max(ans, tp);
        }
        cout << ans << endl;
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