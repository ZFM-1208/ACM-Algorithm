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
    int n, k; cin >> n >> k;
    string s; cin >> s;
    int ans = 0;
    for(int i = 0; i < n; i += k){
        int ok = 1;
        for(int j = i; j <= i+k-1; j++){
            if(s[j] == '0'){
                ok = 0;
                break;
            }
        }
        if(ok) ans++;
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