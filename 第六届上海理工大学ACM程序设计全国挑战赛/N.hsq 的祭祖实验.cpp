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
    s = " " + s + s;
    int ans = 0;
    for(int r = 1; r <= 4; r++){
        vii a(2*n+1);
        for(int i = 1; i <= n; i++){
            int res = 0;
            for(int j = 0; j <= 3; j++){
                int x = s[r + 4 * (i-1) + j] - '0';
                res = res * 2 + x;
            }
            a[i+n] = a[i] = res;
        }
        
        vii vis(2*n+1), pre(2*n+1);
        for(int i = 1; i <= 2*n; i++){
            if(i+2 <= 2*n && a[i] == 1 && a[i+1] == 2 && a[i+2] == 0){
                vis[i] = 1;
            }
            pre[i] = pre[i-1] + vis[i];
        }
        int sum = 0;
        for(int ll = 1; ll <= n; ll++){
            int rr = ll + n - 3;
            int res = pre[rr] - pre[ll-1];
            if(res) sum++;
        }
        ans += sum;
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