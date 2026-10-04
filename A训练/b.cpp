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

// 用 __int128 计算快速幂防中间溢出
__int128 qpow128(__int128 a, int b) {
    __int128 res = 1;
    while (b) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

// 计算 f(b) = (b + d)^k - b^k
__int128 calc_diff(int b, int d, int k) {
    return qpow128(b + d, k) - qpow128(b, k);
}

// 安全计算 b 的理论上界：b^(k-1) <= n / (k * d)
int get_b_max(int val, int exp) {
    int low = 1, high = 6e8, res = 0;
    while (low <= high) {
        int mid = (low + high) / 2;
        __int128 p = 1;
        bool ok = true;
        rep(i, 1, exp) {
            if (p > (__int128)val / mid) { 
                ok = false; 
                break; 
            }
            p *= mid;
        }
        if (ok) {
            res = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return res;
}

void solve(){
    int n, k; 
    cin >> n >> k; //[cite: 9]

    int ans = 0;

    // 枚举差值 d，满足 d^k < n 且 d <= 10^6
    for (int d = 1; ; d++) {
        // 判断 d^k 是否已经 >= n
        __int128 dk = 1;
        bool overflow = false;
        rep(i, 1, k) {
            if (dk > (__int128)n / d) {
                overflow = true;
                break;
            }
            dk *= d;
        }
        if (overflow || dk >= n) break; // d 超过上限，退出循环

        // 必须满足 d 整除 n
        if (n % d != 0) continue;

        // 若甚至连最小的 b=1 时都不满足 n > k * d，则无需二分
        if (n <= k * d) continue;

        // 计算 b 的安全二分上限
        int b_max = get_b_max(n / (k * d), k - 1);
        if (b_max < 1) continue;

        // 二分寻找唯一的 b
        int low = 1, high = b_max;
        while (low <= high) {
            int mid = (low + high) / 2;
            __int128 cur = calc_diff(mid, d, k);
            if (cur == n) {
                ans++;
                break; // 找到了唯一的 b，直接跳出
            } else if (cur < n) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }

    cout << ans << endl; //[cite: 9]
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T = 1;
    cin >> T; //[cite: 9]
    while (T--)
        solve();
    return 0;
}