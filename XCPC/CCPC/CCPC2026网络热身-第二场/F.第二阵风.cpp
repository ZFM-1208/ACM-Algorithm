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
    int n; cin >> n;
    vii a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    /*
        l1: i 左边第 1 个大于 a[i] 的下标
        l2: i 左边第 2 个大于 a[i] 的下标 (不存在则 0 )
        <1>: 最大值在i左边
        ans += (l1 - l2) * (r1 - i) * (i - l1)

        r1: i 右边第 1 个大于 a[i] 的下标
        r2: i 右边第 2 个大于 a[i] 的下标 (不存在则 n+1 )        
        <2>: 最大值在i右边
        ans += (i - l1) * (r2 - r1) * (r1 - i)

    */
    vector<vii> st(n+1,vii(20));
    /*
        st[i][j]: 表示从下标i开始、长度为2^j的闭区间 [i, i + 2^j - 1]内的最值
        st[i][j] = max(st[i][j-1], st[i + 2 ^ (j-1)][j-1]);
    */    
    for(int i = 1; i <= n; i++){
        st[i][0] = a[i];
    }
    for(int j = 1; (1 << j) <= n; j++){
        for(int i = 1; i + (1 << j) - 1 <= n; i++){
            st[i][j] = max(st[i][j-1], st[i + (1 << (j-1))][j-1]);
        }
    }
    auto query = [&](int l, int r) -> int {
        int len = (r - l + 1);
        int k = __lg(len); // log2(len)
        return max(st[l][k], st[r - (1 << k) + 1][k]);
    };

    int ans = 0;
    for(int i = 1; i <= n; i++){
        int l1 = 0;
        int l = 1, r = i-1;
        while(l <= r){
            int mid = (l + r) / 2;
            if(query(mid, i-1) > a[i]){
                l1 = mid;
                l = mid + 1;
            }else{
                r = mid - 1;
            }
        }
        int l2 = 0; // [1, l1 - 1]
        if(l1 > 1){
            l = 1, r = l1-1;
            while(l <= r){
                int mid = (l + r) / 2;
                if(query(mid, l1-1) > a[i]){
                    l2 = mid;
                    l = mid + 1;
                }else{
                    r = mid - 1;
                }
            }
        }
        int r1 = n+1;
        l = i+1, r = n;
        while(l <= r){
            int mid = (l + r) / 2;
            if(query(i+1,mid) > a[i]){
                r1 = mid;
                r = mid - 1;
            }else{
                l = mid + 1;
            }
        }
        int r2 = n+1; // [r1 + 1, n]
        if(r1 < n){
            l = r1+1, r = n;
            while(l <= r){
                int mid = (l + r) / 2;
                if(query(r1+1,mid) > a[i]){
                    r2 = mid;
                    r = mid - 1;
                }else{
                    l = mid + 1;
                }
            }
        }
        if(l1 >= 1){
            ans += (l1 - l2) * (r1 - i) * (i - l1);
        }
        if(r1 <= n){
            ans += (i - l1) * (r2 - r1) * (r1 - i);
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