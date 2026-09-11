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

void solve(){
    int n; cin >> n;
    string s; cin >> s;
    s = " " + s;
    if(s[1] == '0'){
        cout << -1 << endl;
        return;
    }
    for(int i = 2; i <= n; i++){
        if(s[i] == s[i-1] && s[i] == '0'){
            cout << -1 << endl;
            return;
        }
    }
    /*
        1 1 -1 -1 -1 -1 1 -1 1
        1 2 1 1 -2 -3 -2 -3 -2
    */
    /*
        + - - +
        1 -1 -2 3 
    */

    vector<vii> dp1(n + 1, vii(9));
    dp1[0][2] = 1; 
    int as1 = 1;
    for(int i = 1; i <= n; i++){
        bool ok = 0;
        for(int u = -2; u <= 2; u++){
            if(dp1[i - 1][u + 2] == 0) continue;
            for(int dd = -1; dd <= 1; dd++){
                if(dd == 0) continue;
                int v = u + dd;
                if(v < -2 || v > 2) continue; 
                if(s[i] == '+' && v > 0) {
                    dp1[i][v + 2] = 1;
                    ok = 1;
                } else if(s[i] == '-' && v < 0) {
                    dp1[i][v + 2] = 1;
                    ok = 1;
                } else if(s[i] == '0' && v == 0) {
                    dp1[i][v + 2] = 1;
                    ok = 1;
                }
            }
        }
        if (!ok) {
            as1 = 0;
            break;
        }
    }
    if(as1){
        cout << 1 << endl;
        return;
    }
    // cout << "----------->   222222";
    vector<vii> dp2(n+1, vii(9));
    dp2[0][2] = 1;
    int as2 = 1;
    for(int i = 1; i <= n; i++){
        bool ok = 0;
        for(int u = -2; u <= 2; u++){
            if(dp2[i-1][u+2] == 0) continue;
            for(int dd = -2; dd <= 2; dd++){
                if(dd == 0) continue;
                int v = u + dd;
                if(v < -2 || v > 2) continue;
                if(s[i] == '+' && v > 0) {
                    dp2[i][v+2] = 1;
                    ok = 1;
                } else if(s[i] == '-' && v < 0) {
                    dp2[i][v+2] = 1;
                    ok = 1;
                } else if(s[i] == '0' && v == 0) {
                    dp2[i][v+2] = 1;
                    ok = 1;
                }
            }
        }
        if(ok == 0) {
            as2 = 0;
            break;
        }
    }
    if(as2){
        cout << 2 << endl;
        return;
    }
    cout << 3 << endl;
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