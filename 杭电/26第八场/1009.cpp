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
const int N = 2e6+5, mod = 998244353, inf = 1e18 + 5;
int ksm(int a, int b) {
    int res = 1;
    a %= mod;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
int fact[N], inv[N];
void init() {
    fact[0] = inv[0] = 1;
    for (int i = 1; i < N; i++) fact[i] = fact[i - 1] * i % mod;
    inv[N - 1] = ksm(fact[N - 1], mod - 2);
    for (int i = N - 2; i >= 1; i--) inv[i] = inv[i + 1] * (i + 1) % mod;
}

int C(int n, int m) {
    if (n < 0 || m < 0 || n < m) return 0;
    return fact[n] * inv[m] % mod * inv[n - m] % mod;
}

void solve(){
    int n; cin >> n;
    vii p(2*n+1),vis(2*n+1);
    for(int i = 1; i <= 2*n; i++) {
        cin >> p[i];
        vis[p[i]] = 1; 
    }
    int s = 0, d = 0;
    vector<int> a; 
    a.pb(0);
    for(int i = 1; i <= 2*n; i += 2){
        if(p[i] == 0 && p[i+1] == 0){
            d++; // 双空对
        }else if(p[i] == 0 || p[i+1] == 0){
            s++; // 单空对
            if(p[i]) a.pb(p[i]);
            if(p[i+1]) a.pb(p[i+1]);
        }
    }
    sort(a.begin()+1, a.end());
    vector<int> b;
    b.pb(0); 
    for(int i = 2*n; i >= 1; i--){
        if(vis[i] == 0) b.pb(i);
    }
    int pos = 0;
    while(pos < s){
        if(b[d+pos+1] > a[pos+1]){
            pos++;
        }else{
            break;
        }
    }
    int ans = (fact[d + pos] * fact[d + s - pos]) % mod;
    ans = (ans * ksm(2,d)) % mod;
    cout << ans << endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T = 1;
    init();
    cin >> T;
    while(T--)
        solve();
    return 0;
}