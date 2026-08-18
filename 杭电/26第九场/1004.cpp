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

struct LB {
    int d[64];
    void init() {
        memset(d, 0, sizeof(d));
    }
    bool insert(int val) {
        for (int i = 62; i >= 0; i--) {
            if ((val >> i) & 1) {
                if (!d[i]) {
                    d[i] = val;
                    return true;
                }
                val ^= d[i];
            }
        }
        return false;
    }
    int query_max(int x) {
        int res = x;
        for (int i = 62; i >= 0; i--) {
            if ((res ^ d[i]) > res) {
                res ^= d[i];
            }
        }
        return res;
    }
} lb;

void solve() {
    int n, len, q;
    cin >> n >> len >> q;
    vii a(n + 1), pre(n + 1, 0);
    rep(i, 1, n) {
        cin >> a[i];
        pre[i] = pre[i - 1] ^ a[i];
    }
    lb.init();

    for (int i = 1; i + len - 1 <= n; i++) {
        int x = pre[i + len - 1] ^ pre[i - 1];
        lb.insert(x);
    }
    while (q--) {
        int x; cin >> x;
        cout << lb.query_max(x) << endl;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T = 1;
    if (cin >> T) {
        while (T--) solve();
    }
    return 0;
}