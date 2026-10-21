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
    int n, k;cin >> n >> k;
    vii cnt(k, 0);
    int mx = 0;
    for(int i = 1; i <= n; i++){
        int x; cin >> x;
        if (x >= 1 && x <= k) {
            int p = ((x - i) % k + k) % k;
            cnt[p]++;
            mx = max(mx, cnt[p]);
        }
    }
    cout << n - mx << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}