#include <bits/stdc++.h>
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
const int N = 1e7+10, M = 7e5 + 10, mod = 1e9 + 7, inf = 1e18 + 5;
int primes[M],cnt,fact[20],num;
bool vis[N];
void get_primes(int n){
    cnt = 0;
    vis[0] = vis[1] = 1;
    // for(int i = 1; i <= n; i++) vis[i] = 0;
    for(int i = 2; i <= n; i++){
        if(!vis[i]) primes[++cnt] = i;
        for(int j = 1; j <= cnt && i * primes[j] <= n; j++){
            vis[i * primes[j]] = 1;
            if(i % primes[j] == 0) break;
        }
    }
}
void get_fact(int n){
    num = 0;
    for(int i = 1; i <= cnt && primes[i] * primes[i] <= n; i++){
        if(n % primes[i] == 0){
            fact[num++] = primes[i];
            while(n % primes[i] == 0) 
                n /= primes[i];
        }
    }
    if(n > 1) fact[num++] = n;
}
int get(int m){
    int res = 0;
    for(int i = 1; i < (1LL << num); i++){
        int sum = 0LL;
        int temp = 1LL;
        bool ok = true;
        for(int j = 0; j < num; j++){
            if(i & (1LL << j)){
                if(temp > m / fact[j]){
                    ok = false;
                    break;
                }              
                sum++;
                temp *= fact[j];

            }
        }
        if(!ok) continue;
        if(sum % 2) res += m / temp;
        else res -= m / temp;
    }
    return res;
}
void solve(){
    int l,r,n; 
    cin >> l >> r >> n;
    get_fact(n);
    int p = n-1;
    while(p >= 2 && vis[p]) p--;
    if(p < 2) p = 1;
    int ans = 0;
    int R = min(r, p-1);
    // x < p
    if(l <= R){
        int len = R - l + 1;
        ans += len + get(R) - get(l-1);
    }
    // [p, n]
    // dp[u] = min(gcd(u,v) + dp[v]), u<v<=n
    vector<int> dp(n-p+1, inf);
    dp[n-p] = 0;
    for(int u = n - 1; u >= p; u--){
        for(int v = u + 1; v <= n; v++){
            dp[u - p] = min(dp[u - p],dp[v - p] + __gcd(u, v));
        }
    }

    for(int i = max(l, p); i <= r; i++){
        ans += dp[i-p];
    }
    // vector<int> dp(n+1, inf);
    // dp[n] = 0;
    // for(int u = n - 1; u >= p; u--){
    //     for(int v = u + 1; v <= n; v++){
    //         dp[u] = min(dp[u], dp[v] + __gcd(u, v));
    //     }
    // }
    // for(int i = max(l, p); i <= r; i++){
    //     ans += dp[i];
    // }
    cout << ans << endl;

    // vector<vector<int>> dist(n+1,vector<int>(n+1,inf));
    // for(int i = 1; i <= n; i++){
    //     dist[i][i] = 0;
    //     for(int j = i+1; j <= n; j++){
    //         dist[i][j] = __gcd(i,j);
    //     }
    // }
    // for(int k = 1; k <= n; k++){
    //     for(int i = 1; i <= n; i++){
    //         for(int j = 1; j <= n; j++){
    //             dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    //         }
    //     }
    // }
    // for(int i = 1; i <= n; i++){
    //     cout << "i: " << i << " j:" << " " << n << " " << dist[i][n] << " \n";
    // }
    // int sum = 0;
    // for(int i = l; i <= r; i++){
    //     sum += dist[i][n];
    // }
    // cout << sum << endl;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    get_primes(N - 1);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
