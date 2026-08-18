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
    vii a(n+2),b(n+2);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    int sum = 0;
    for(int i = 1; i < n; i++){
        if(i > 1) b[i] = a[i+1] + a[i+1];
        sum += (a[i] - a[i+1]) * (a[i] - a[i+1]);
    }
    int ans = 0;
    if(n <= 200) {// 8e6
        for(int i = 1; i <= n; i++){
            for(int j = i+1; j <= n; j++){
                swap(a[i], a[j]);
                int res = 0; 
                for(int q = 1; q < n; q++){
                    res += (a[q] - a[q+1]) * (a[q] - a[q+1]);
                }
                if(res > sum){
                    ans++;
                }
                swap(a[i], a[j]);
            }
        }
        cout << ans << endl;
        return;
    }
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