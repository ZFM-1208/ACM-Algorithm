#include<bits/stdc++.h>
using namespace std;
#define rep(i, l, r) for(int i = l; i <= r; i++)
#define vii vector<int>
#define pii pair<int, int>
#define int long long
#define pb push_back
#define fi first
#define se second
#define endl '\n'
double pi = acos(-1);
const int N = 2e5+10, mod = 1e9+7, inf = 1e18 + 5;

int ksm(int a, int b){
    int res = 1;
    a %= mod;
    while(b){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int fact[N], inv[N];
void init(){
    fact[0] = inv[0] = 1;
    for(int i = 1; i < N; i++) fact[i] = fact[i - 1] * i % mod;
    inv[N - 1] = ksm(fact[N - 1], mod - 2);
    for(int i = N - 2; i >= 1; i--) inv[i] = inv[i + 1] *(i + 1) % mod;
}

int C(int n, int m){
    if(n < 0 || m < 0 || n < m) return 0;
    return fact[n] * inv[m] % mod * inv[n - m] % mod;
}

void solve(){
    int n; cin >> n;
    vii a(n + 1); 
    map<int, int> mp; 
    int cf1 = 0;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        if(a[i] == -1){
            cf1++;
        }else{
            mp[a[i]]++;
        }
    }
    int cs = 1;
    for(auto [x,y] : mp){
        cs = cs * ksm(2, y - 1) % mod; 
    }
    int cn = 0;
    for(auto [x,y] : mp){
        if(mp.count(x + 1)){ 
            cn++;
        }
    }
    int ans = 0;
    if(cf1 == 0){
        ans = cs; 
    }else{
        int sj = ksm(2, cf1 - 1) * cs % mod;
        int so = ksm(2, cf1 - 1) * cs % mod * cn % mod;
        ans =(sj + so) % mod;
    }
    cout << ans << endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    // init(); 
    int T = 1;
    cin >> T;
    while(T--)
        solve();
    return 0;
}