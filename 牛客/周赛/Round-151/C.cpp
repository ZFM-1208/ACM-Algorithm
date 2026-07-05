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
    string a,b; cin >> a >> b;
    int na = a.size();
    int nb = b.size();
    int la = na, lb = nb;
    for(int i = 0; i < na; i++){
        if(a[i] == '.'){
            la = i;
            break;
        }
    }
    for(int i = 0; i < nb; i++){
        if(b[i] == '.'){
            lb = i;
            break;
        }
    }
    /*
        012345678
        123.12300
        009.12345

    */
    int ra = na - la - 1;
    int rb = nb - lb - 1;
    if(la < lb){
        int nn = lb - la;
        while(nn--){
            a = "0" + a;
        }
    }
    if(la > lb){
        int nn = la - lb;
        while(nn--){
            b = "0" + b;
        }
    }
    if(ra < rb){
        int nn = rb - ra;
        while(nn--){
            a = a + "0";
        }
    }
    if(ra > rb){
        int nn = ra - rb;
        while(nn--){
            b = b + "0";
        }
    }
    int op = 0;
    int ans = 0;
    for(int i = a.size() - 1; i >= 0; i--){
        if(a[i] == '.') continue;
        int sum = (a[i] - '0') + (b[i] - '0') + op;
        if(sum >= 10){
            ans++;
            op = 1;
        }else{
            op = 0;
        }
    }
    cout << ans << endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    return 0;
}