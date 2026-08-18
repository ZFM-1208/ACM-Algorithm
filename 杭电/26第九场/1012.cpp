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

struct BIT {
    int n;
    vector<int> tr;
    BIT(int _n = 0) : n(_n), tr(_n + 1, 0) {}
    int lowbit(int x) { return x & -x; }
    
    void add(int x, int c) {
        for (int i = x; i <= n; i += lowbit(i)) tr[i] += c;
    }
    
    int query(int x) {
        int res = 0;
        for (int i = x; i > 0; i -= lowbit(i)) res += tr[i];
        return res;
    }
    
    int query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};
// <1>: n > j > i+1 > 2
// (1) a[i] > a[j] && a[i-1] + a[i+1] > a[j-1] + a[j+1]
// (2) a[i] < a[j] && a[i-1] + a[i+1] < a[j-1] + a[j+1]

// <2>: j = i+1
// (1) a[i] > a[j] && a[i-1] > a[j+1]
// (2) a[i] < a[j] && a[i-1] < a[j+1]
void solve(){
    int n;  cin >> n;
    vii a(n + 2), b(n + 2);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    int sum = 0;
    for(int i = 1; i < n; i++){
        if(i > 1) b[i] = a[i-1] + a[i+1];
        sum += (a[i] - a[i+1]) * (a[i] - a[i+1]);
    }
    int ans = 0;
    if(n <= 200) {// 8e6
        for(int i = 1; i <= n; i++){
            for(int j = i+1; j <= n; j++){
                swap(a[i], a[j]);
                int res = 0; 
                for(int q = 1; q < n; q++){
                    res += (a[q] - a[q+1]) * (a[q] - a[q+1]);
                }
                if(res > sum){
                    ans++;
                }
                swap(a[i], a[j]);
            }
        }
        cout << ans << endl;
        return;
    }
    vector<array<int,3>> p(n-1);
    vii val;
    for(int i = 2; i <= n - 1; i++){
        p[i-1] = {a[i], b[i], i};
        val.pb(b[i]);
    }
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());
    int sz = val.size();
    auto get = [&](int v) -> int {
        return lower_bound(val.begin(), val.end(), v) - val.begin() + 1;
    };

    sort(p.begin() + 1, p.end(), [&](auto op1, auto op2){
        if(op1[0] == op2[0]) return op1[1] < op2[1];
        return op1[0] < op2[0];
    });

    BIT bit(sz);
    int l = 1;
    while(l <= n-2){
        int r = l;
        while(r + 1 <= n-2 && p[r + 1][0] == p[l][0]) r++;
        for(int i = l; i <= r; i++){
            int rk = get(p[i][1]);
            ans += bit.query(rk - 1);
        }
        for(int i = l; i <= r; i++){
            int rk = get(p[i][1]);
            bit.add(rk, 1);
        }
        l = r + 1;
    }
    
    for(int i = 2; i <= n-2; i++){
        if((a[i] - a[i+1]) * (b[i] - b[i+1]) > 0) ans--;
    }
    // sap(i,i+1)
    for(int i = 1; i < n; i++){
        vii cun;
        if(i-1 >= 1) cun.pb(i - 1);
        cun.pb(i);
        if(i+1 < n) cun.pb(i+1);
        sort(cun.begin(), cun.end());
        cun.erase(unique(cun.begin(), cun.end()), cun.end());
        int s1 = 0, s2 = 0;
        for(int x: cun){
            s1 += (a[x] - a[x + 1]) * (a[x] - a[x + 1]);
        }
        swap(a[i], a[i+1]);
        for(int x: cun){
            s2 += (a[x] - a[x + 1]) * (a[x] - a[x + 1]);
        }
        swap(a[i], a[i+1]);
        if(s2 > s1) ans++;
    }
    // swap(1,j) // 0,1,j-1,j
    for(int j = 3; j <= n; j++){
        vii cun;
        cun.pb(1);
        cun.pb(j - 1);
        if(j < n) cun.pb(j);
        sort(cun.begin(), cun.end());
        cun.erase(unique(cun.begin(), cun.end()), cun.end());
        int s1 = 0, s2 = 0;
        for(int x: cun){
            s1 += (a[x] - a[x + 1]) * (a[x] - a[x + 1]);
        }
        swap(a[1], a[j]);
        for(int x: cun){
            s2 += (a[x] - a[x + 1]) * (a[x] - a[x + 1]);
        }
        swap(a[1], a[j]);
        if(s2 > s1) ans++;
    }
    // swap(i,n); // i-1,i,n-1,n
    for(int i = 2; i <= n-2; i++){
        vii cun;
        cun.pb(i - 1);
        cun.pb(i);
        cun.pb(n - 1);
        sort(cun.begin(), cun.end());
        cun.erase(unique(cun.begin(), cun.end()), cun.end());
        int s1 = 0, s2 = 0;
        for(int x: cun){
            s1 += (a[x] - a[x + 1]) * (a[x] - a[x + 1]);
        }
        swap(a[i], a[n]);
        for(int x: cun){
            s2 += (a[x] - a[x + 1]) * (a[x] - a[x + 1]);
        }
        swap(a[i], a[n]);
        if(s2 > s1) ans++;
    }
    cout << ans << endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();
    return 0;
}
