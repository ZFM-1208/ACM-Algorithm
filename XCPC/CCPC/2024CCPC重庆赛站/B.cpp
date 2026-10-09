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
#define ld long double
void solve()
{
    int pm; cin >> pm;
    ld a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;
    ld acc = 1000 * (300*a + 300*b + 200*c + 100*d + 50*e)  / (3 * (a + b + c + d + e + f));
    ld pp = ( (320*a + 300*b + 200*c + 100*d + 50*e) *5*pm  / (32 * (a + b + c + d + e + f) ) - 40.0*pm);
    pp = max(pp, (ld)0.0);
    // acc = acc * 100000;
    // acc = 96202.627104;
    int op = acc;
    if(op % 10 >= 5) op +=10;
    op /= 10;
    double ans1 = (ld)op / 100.0;
    // cout << fixed << setprecision(6) << acc << endl;


    cout << fixed << setprecision(2) << ans1 << "% ";

    int opp = pp;
    int ok = 0;
    if(opp % 10 >= 5)  ok++;
    opp /= 10;
    opp += ok;
    int ans2 = opp;
    cout << ans2 << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}