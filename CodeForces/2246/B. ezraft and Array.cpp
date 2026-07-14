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
const int N = 1e6, mod = 1e9+7, inf = 1e18 + 5;
/*
    s / xi = ai;
    a1 + a2 + a3 + ... + an = s/x1 + s/x2 + s/x3 + ... + s / xn = s;
    so:  1/x1 + 1/x2 + 1/x3 + 1/x4 + ... + 1/xn = 1;
    当n = 1:  x1 = 1;   
    a1 = 1;
    n = 2: x1 = x2(不合法)

    n = 3: x1 = 6, x2 = 3, x3 = 2; S = 6; 1/2 + 1/3 + 1/6 = 1;
    a1 = 1, a2 = 2, a3 = 3;

    由于是构造体，我们希望a[]构造的前面尽可能不变，让新加进来的数依旧满足
    n = 4;
    a1 = 1, a2 = 2, a3 = 3, a4 = ?
    S' = S + a4 依旧可以整除 a1,a2,a3
    且S'还能整数a4
    so: a4是S的倍数, a4是S的因子:  a4 = S

    a[]:
    1,2,3,6,12,24,48......
*/
void solve(){
    int n; cin >> n;
    if(n == 1){
        cout << 1 << endl;
        return;
    }
    if(n == 2){
        cout << -1 << endl;
        return;
    }
    vii a(n+1);
    a[1] = 1;
    a[2] = 2;
    a[3] = 3;
    int sum = 6;
    for(int i = 4; i <= n; i++){
        a[i] = sum;
        sum += a[i];
    }
    rep(i,1,n) cout << a[i] << " \n"[i==n];
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();
    return 0;
}