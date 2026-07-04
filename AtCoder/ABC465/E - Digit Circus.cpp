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
const int N = 1e6, mod = 998244353, inf = 1e18 + 5;

/*
    dp[i][p][st][rem][mask]
    i 已经填了前 i 位。

    p 当前前缀是否还贴着 N
    p = 1：目前填出来的前缀和 N 的前缀一样
    p = 0：目前填出来的前缀已经比 N 小了

    st 是否已经开始组成数字
    st = 0：目前全是前导 0，还没有真正开始。
    st = 1：已经填过非 0 数字。

    rem 当前数字对 3 取模的值。

    mask 当前数字里出现过哪些数字
    比如第 3 位是 1，表示出现过数字 3。
*/
int dp[505][2][2][3][1024];

void solve(){
    string s; cin >> s;
    int n = s.size();
    // 一开始处理了 0 位
    // 当前前缀和 N 相同，所以 p = 1
    // 还没有开始组成数字，所以 st = 0
    // 当前余数是 0，数字集合为空
    dp[0][1][0][0][0] = 1;
   
    for(int i = 0; i < n; i++){ // 表示处理第 i + 1 位
        int up = s[i] - '0';
        for(int p = 0; p <= 1; p++){
            for(int st = 0; st <= 1; st++){
                for(int rem = 0; rem < 3; rem++){
                    for(int mask = 0; mask < 1024; mask++){
                        int cur = dp[i][p][st][rem][mask];
                        if(cur == 0) continue;
                        int lim; // 确定填数上限
                        if(p) lim = up;
                        else lim = 9;

                        for(int d = 0; d <= lim; d++){ // 然后枚举这一位填什么数字
                            int np = p && (d == up);
                            // 还没有开始，并且这一位继续填 0
                            // 这个 0 是前导零，不算进数字
                            if(st == 0 && d == 0){
                                dp[i + 1][np][0][0][0] += cur;
                                dp[i + 1][np][0][0][0] %= mod;
                            }else{
                                // 已经开始组成数字
                                int nst = 1;
                                int nrem = (rem * 10 + d) % 3;
                                int nmask = mask | (1 << d);
                                dp[i + 1][np][nst][nrem][nmask] += cur;
                                dp[i + 1][np][nst][nrem][nmask] %= mod;
                            }
                        }
                    }
                }
            }
        }
    }
    int ans = 0;
    for(int p = 0; p <= 1; p++){
        for(int rem = 0; rem < 3; rem++){
            for(int mask = 0; mask < 1024; mask++){
                int cur = dp[n][p][1][rem][mask];
                if(cur == 0) continue;
                int cnt = 0;
                if(rem == 0) cnt++;
                if(mask & (1 << 3)) cnt++;
                if(__builtin_popcount((int)mask) == 3) cnt++;
                if(cnt == 1){
                    ans += cur;
                    ans %= mod;
                }
            }
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