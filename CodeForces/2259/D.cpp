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
    vii a(n+1);
    vii cun;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        if(a[i] == 0) cun.pb(i);
    }
    if(cun.size() == 0){
        cout << "YES" << endl;
        cout << "AB";
        for(int i = 3; i <= n; i++){
            cout << "C";
        }
        cout << endl;
    }else if(cun.size() == 1){
        cout << "NO" << endl;
    }else if(cun.size() >= 2){
        cout << "YES" << endl;
        vii ans(n+1,0);
        for(int i: cun){
            ans[i] = 1;
        }
        ans[cun[0]] = 2;
        for(int i = 1; i <= n; i++){
            if(ans[i] == 0){
                cout << "C";
            }else if(ans[i] == 1){
                cout << "A";
            }else{
                cout << "B";
            }
        }
        cout << endl;
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