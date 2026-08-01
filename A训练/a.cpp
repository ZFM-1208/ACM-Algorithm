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
const int N = 1e7+10, mod = 998244353, inf = 1e18 + 5;
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
int cnt = 0;
int pri[N+10];
int vis[N+10];
void init() {
    pri[0] = 1;
    vis[1] = 1;
    for(int i = 2; i <= N; i++) {
        if(!vis[i]) {
            pri[++cnt] = i;
            vis[i] = 1;
        }
        for(int j = 1; j <= cnt && pri[j] * i <= N; j++) {
            vis[i * pri[j]] = vis[i] + 1;
            if(i % pri[j] == 0) break;
        }
    }
}
void solve() {
    int n,c;
    cin >> n  >> c;
    int ans = 0;
    int ccc = 1;
    for(int i = 1; i <= n; i++) {
        int k=0;
        k = vis[i];
        ans = (ans + pri[k-1] * ksm(c,i) % mod) % mod;
    }

    cout << ans << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    init();
    // cin >> T;
    while(T--)
        solve();
    return 0;
}