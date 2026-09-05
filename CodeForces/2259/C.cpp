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
        if(a[i] == 1) cun.pb(i);        
    }
    if(cun.size() == 0){
        vii c;
        for(int i = 1; i <= n; i++){
            if(a[i] == -1){
                a[i] = 0;
                c.pb(i);
            }
        }
        if(c.size() != 0)  a[c.front()] = a[c.back()] = 1;
        rep(i,1,n) cout << a[i] << " \n"[i==n];
        return;
    }
    int mx = 0;
    int op = 0; 
    for(int j = 0; j < cun.size() - 1; j++){
        int len = cun[j + 1] - cun[j] + 1;
        if(len > mx){
            mx = len;
            op = 0;
        }
    }
    int L = -1;
    for(int i = 1; i < cun.front(); i++){
        if(a[i] == -1){
            int len = cun.front() - i + 1;
            if(len > mx){
                mx = len;
                op = 1;
                L = i;
            }
            break;
        }
    }
    int R = -1;
    for (int i = n; i > cun.back(); i--){
        if(a[i] == -1){
            int len = i - cun.back() + 1;
            if(len > mx){
                mx = len;
                op = 2;
                R = i;
            }
            break;
        }
    }
    
    rep(i, 1, n){
        if(a[i] == -1) a[i] = 0;
        if(i == L && op == 1) a[i] = 1;
        if(i == R && op == 2) a[i] = 1;
        cout << a[i] << " \n"[i == n];
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