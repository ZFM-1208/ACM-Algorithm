#include <bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for (int i = l; i <= r; i++)
#define vii vector<int>
#define int long long
#define endl '\n'

const int MOD = 998244353;

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    int max_val = m + 2;

    // dp[v] 表示当前位置数值为 v 的方案数
    vii dp(max_val + 2, 0);
    dp[max_val] = 1;

    int ans = 0;

    // 最多向后走 n - 1 步 (对应 L = 2 到 n)
    rep(step, 1, n - 1) {
        // 1. 预处理后缀和
        vii suf(max_val + 3, 0);
        for (int v = max_val; v >= 2; v--) {
            suf[v] = (suf[v + 1] + dp[v]) % MOD;
        }

        // 2. O(1) 转移计算新一层的状态
        vii new_dp(max_val + 2, 0);
        rep(u, 2, max_val) {
            int r = min(max_val, 2 * u - 1);
            new_dp[u] = (suf[u] - suf[r + 1] + MOD) % MOD;
        }

        // 3. 凡是在当前步到达数值 2 的，对应一个唯一的合法 L，计入答案
        ans = (ans + new_dp[2]) % MOD;

        dp = move(new_dp);
    }

    cout << ans << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        while (t--) solve();
    }
    return 0;
}