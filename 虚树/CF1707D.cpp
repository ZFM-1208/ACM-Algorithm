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

void solve() {
    int n, mod;
    if (!(cin >> n >> mod)) return;

    vector<vii> adj(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    // 预处理组合数
    vector<vii> C(n + 1, vii(n + 1, 0));
    for (int i = 0; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
        }
    }

    // dp[u][i]: u子树在恰好第 i 步删完的方案数
    // S[u][i]:  u子树在 <= i 步删完的方案数
    vector<vii> dp(n + 1, vii(n + 1, 0));
    vector<vii> S(n + 1, vii(n + 1, 0));

    auto dfs = [&](auto& self, int u, int p) -> void {
        vii sons;
        for (int v : adj[u]) {
            if (v == p) continue;
            self(self, v, u);
            sons.pb(v);
        }

        int m = sons.size();
        if (m == 0) { // 叶子节点
            for (int i = 1; i <= n; i++) {
                dp[u][i] = 1;
                S[u][i] = i % mod;
            }
            return;
        }

        // H[j] 维护子节点 sons[j] 的历史累加系数 sum_{t=1}^{i-1} prod_{w != sons[j]} S[w][t]
        vii H(m, 0);
        vii pre(m + 2, 1), suf(m + 2, 1);

        for (int i = 1; i <= n; i++) {
            // 1. 利用 i-1 步的状态更新 H
            if (i > 1) {
                pre[0] = 1;
                for (int j = 0; j < m; j++) {
                    pre[j + 1] = pre[j] * S[sons[j]][i - 1] % mod;
                }
                suf[m + 1] = 1;
                for (int j = m - 1; j >= 0; j--) {
                    suf[j + 1] = suf[j + 2] * S[sons[j]][i - 1] % mod;
                }
                for (int j = 0; j < m; j++) {
                    int other_prod = pre[j] * suf[j + 2] % mod;
                    H[j] = (H[j] + other_prod) % mod;
                }
            }

            // 2. 计算 u 本身在第 i 步被删除的贡献 (所有子节点 <= i 步删完)
            int term1 = 1;
            for (int j = 0; j < m; j++) {
                term1 = term1 * S[sons[j]][i] % mod;
            }

            // 3. 计算 u 在 t < i 步被删除的贡献 (非根节点才有该项)
            int term2 = 0;
            if (u != 1) {
                for (int j = 0; j < m; j++) {
                    term2 = (term2 + dp[sons[j]][i] * H[j]) % mod;
                }
            }

            dp[u][i] = (term1 + term2) % mod;
            S[u][i] = (S[u][i - 1] + dp[u][i]) % mod;
        }
    };

    dfs(dfs, 1, 0);

    // 计算 g(k): 至多 k 步的方案数
    vii g(n + 1, 0);
    vii sons_root;
    for (int v : adj[1]) sons_root.pb(v);

    for (int k = 1; k < n; k++) {
        int cur = 1;
        for (int v : sons_root) {
            cur = cur * S[v][k] % mod;
        }
        g[k] = cur;
    }

    // 容斥求 f(k): 恰好 k 步的方案数
    vii f(n + 1, 0);
    for (int k = 1; k < n; k++) {
        f[k] = g[k];
        for (int i = 1; i < k; i++) {
            f[k] = (f[k] - C[k][i] * f[i]) % mod;
            if (f[k] < 0) f[k] += mod;
        }
    }

    // 输出答案 k = 1, 2, ..., n - 1
    for (int k = 1; k < n; k++) {
        cout << f[k] << (k == n - 1 ? "" : " ");
    }
    cout << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}