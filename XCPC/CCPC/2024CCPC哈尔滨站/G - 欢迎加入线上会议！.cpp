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
const int N = 1e6, mod = 1e9 + 7, inf = 1e18 + 5;
void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int> > e(n + 1);
    vector<int> vis(n + 5);
    for (int i = 1; i <= k; i++)
    {
        int x;
        cin >> x;
        vis[x] = 1;
    }

    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        e[u].pb(v);
        e[v].pb(u);
    }
    int nb = -1;
    for (int i = 1; i <= n; i++)
    {
        if (vis[i] == 0)
        {
            nb = i;
            break;
        }
    }
    if (nb == -1)
    {
        cout << "No\n";
        return;
    }
    vector<vector<int> > ans(n + 1);
    vector<int> vv(n + 1);
    vector<int> sx(n + 1);
    vv[nb] = 1;
    int cnt = 0;
    auto dfs = [&](auto &self, int u, int fa) -> void
    {
        
        for (int v : e[u])
        {
            if (v != fa)
            {
                if (vv[v] == 1)
                    continue;
                ans[u].pb(v);
                
                vv[v] = 1;
                if (vis[v] == 0)
                {
                    self(self, v, u);
                }
            }
        }
        if(ans[u].size()) sx[++cnt] = u;
    };
    dfs(dfs, nb, 0);
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += ans[i].size();
    }
    if (sum == n - 1)
    {
        cout << "Yes" << endl;
        cout << cnt << endl;
        for (int i = cnt; i >= 1; i--)
        {
            int d = sx[i];
            cout << d << " " << ans[d].size() << " ";
            for (int j = 0; j < ans[d].size(); j++)
            {
                cout << ans[d][j] << " ";
            }
            cout << "\n";
        }
    }
    else
    {
        cout << "No" << endl;
        return;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}