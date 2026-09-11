#include<bits/stdc++.h>
using namespace std;
#define rep(i, l, r) for(int i = l; i <= r; i++)
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
    12
    21

    213

    2413
    1233

    24135
    12435

    246135
    152463

    3624157
    1572436
*/
void solve(){
    int n;  cin >> n;
    if(n <= 5){
        cout << "No" << endl;
        return;
    }
    cout << "Yes" << endl;
    vii ou, ji;
    rep(i, 1, n){
        if(i&1) ji.pb(i);
        else ou.pb(i);
    }
    if(n % 2 == 0){
        for(int x: ou) cout << x << " ";
        for(int x: ji) cout << x << " ";
        cout << endl;
        for(int x: ji) if(x != 3) cout << x << " ";
        for(int x: ou) if(x != 6) cout << x << " ";
        cout << "6 3"<< endl;
    }else{ 
        cout << "3 6" << " ";     
        for(int x: ou) if(x != 6) cout << x << " ";
        for(int x: ji) if(x != 3) cout << x << " ";
        cout << endl;
        for(int x: ji) if(x != 3) cout << x << " ";
        for(int x: ou) if(x != 6) cout << x << " ";
        cout << "6 3" << endl;;
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();
    return 0;
}