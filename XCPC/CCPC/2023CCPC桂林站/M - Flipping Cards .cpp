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
    最大化中位数x --> 至少存在(n+1)/2个数字 >= x  --> 二分答案
    0/1判定
    区间翻转 -> 贡献转化
    求最大子段和(Kadane) O(n) - 扫描线

*/
void solve(){
    int n; cin >> n;
    vii a(n+1), b(n+1);
    rep(i,1,n) cin >> a[i] >> b[i];
    int l = 1, r = 1e9;
    int ans = 1;
    auto check = [&](int x) -> bool {
        int res = 0;
        int mx = 0;
        int cur = 0;
        for(int i = 1; i <= n; i++){
            int u = (a[i] >= x ? 1 : 0);
            int v = (b[i] >= x ? 1 : 0);
            res += u;
            int dif = v - u;
            cur += dif;
            if(cur < 0) cur = 0;
            mx = max(mx, cur);
        }
        return (res + mx) >= (n+1)/2;
    };
    while(l <= r){
        int mid = (l + r) / 2;
        if(check(mid)){
            ans = mid;
            l = mid + 1;
        }else{
            r = mid - 1;
        }
    }
    cout << ans << endl;
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