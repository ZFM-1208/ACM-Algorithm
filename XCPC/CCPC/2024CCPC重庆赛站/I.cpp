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
const int N = 1e6, mod = 998244353 , inf = 1e18 + 5;
/*
     2 * 7 = 14

     3 * 7 = 21

     2 * 8 = 16

     1和2凑3，3个1凑3，2个1凑2，剩下1加到最小数
*/
void solve(){
    vii a(11);
    for(int i = 1; i <= 9; i++) cin >> a[i];
    while(a[2] >= 1 && a[1] >= 1) {
        a[2]--;
        a[1]--;
        a[3]++;
    }
    while(a[1] >= 3){
        a[1] -= 3;
        a[3]++;
    }
    while(a[1] >= 2){
        a[1] -= 2;
        a[2]++;
    }
    if(a[1]){
        for(int i = 2; i <= 9; i++){
            if(a[i]){
                a[1]--;
                a[i]--;
                a[i+1]++;
                break;
            }
        }
    }
    int ans = 1;
    for(int i = 1; i <= 10; i++){
        while(a[i]--) ans = ans * i % mod;
    }
    cout << ans << endl;
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