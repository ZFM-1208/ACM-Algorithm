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
    vii b(n+1), c(n+2), bj(n+1);
    for(int i = 1; i <= n; i++){
        cin >> b[i];
        if(b[i] > 0){
            int l = i - b[i] + 1;
            int r = i + b[i] - 1;
            l = max(1LL, l);
            r = min(r, n);
            c[l]++;
            c[r+1]--;
        }else if(b[i] == 0){
            bj[i] = 1;
        }
    }
    vii vis(n+1),a(n+1);
    bool ok = 1;
    for(int i = 1; i <= n; i++){
        a[i] = a[i-1] + c[i];
        if(a[i] == 0) {
            ok = 0;
            vis[i] = 1;
        }else{
            if(bj[i] == 1){
                cout << -1 << endl;
                return;
            }
        }
    }
    if(ok == 1){
        cout << -1 << endl;
        return;
    }
    for(int i = 1; i <= n; i++){
        if(b[i] == -1) continue;
        int l = i - b[i];
        int r = i + b[i];
        if(l >= 1 && vis[l] == 1){

        }else if(r <= n && vis[r] == 1){

        }else{
            cout << -1 << endl;
            return;
        }
    }
    rep(i,1,n) cout << vis[i] << 

    
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