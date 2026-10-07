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
const int N = 1e6, mod = 1e9+7, inf = 4e18 + 5;
/*
    3 4 5
    a b c
    b: 4-- 4-3+1 2 
    c: 5-- 5-4+1 2 
*/
void solve(){
    int n,k; cin >> n >> k;
    vector<array<int,3>> arr(n+1);
    vector<int> sum(n+1);
    vector<int> d(n+1);
    int mn = inf;
    for(int i = 1; i <= n; i++){
        cin >> arr[i][0] >> arr[i][1] >> arr[i][2];
        sum[i] = arr[i][0] + arr[i][1] + arr[i][2];
        mn = min(mn, sum[i]);
        if(arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2]){
            d[i] = -1;
        }else if(arr[i][0] <= arr[i][1] && arr[i][1] <= arr[i][2]){
            int d1 = arr[i][1] - arr[i][0] + 1;
            int d2 = arr[i][2] - arr[i][1] + 1;
            d[i] = min(d1,d2);
        }
    }
    auto check = [&](int x) -> bool {
        int tot = 0;
        for(int i = 1; i <= n; i++){
            if(sum[i] >= x) continue;
            if(d[i] == -1) return false;
            int cnt = (x - sum[i]) + 2 * d[i];
            tot += cnt;
            if(tot > k) return false;
        }
        return tot <= k;
    };
    int l = mn, r = mn + k;
    int ans = mn;
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
    cin >> T;
    while(T--)
        solve();
    return 0;
}