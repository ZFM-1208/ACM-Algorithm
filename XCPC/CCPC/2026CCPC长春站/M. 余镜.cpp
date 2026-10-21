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
    int n, M;cin >> n >> M;
    vii a(n + 1);
    rep(i, 1, n) cin >> a[i];
    vector<int> ys(M + 1, 0);
    for (int d = 2; d <= M; d++){
        for (int mul = d; mul <= M; mul += d) {
            ys[mul]++;
        }
    }
    int ans = 0;
    rep(c, 2, 2 * n - 1) {
        int l = c / 2;
        int r = (c + 1) / 2;
        if(l == r){
            l--;
            r++;
        }
        int g = 0;
        while (l >= 1 && r <= n) {
            int diff = abs(a[l] - a[r]);
            if (diff != 0) {
                if (g == 0) {
                    g = diff;
                } else if (diff % g != 0) {
                    g = std::gcd(g, diff);
                }
            }
            if (g == 1) {
                break;
            } else if (g == 0) {
                ans += (M - 1);
            } else {
                ans += ys[g];
            }
            l--;
            r++;
        }
    }
    cout << ans << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}