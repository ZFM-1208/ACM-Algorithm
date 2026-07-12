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
    int k; cin >> k;
    if(k > 21){
        cout << -1 << endl;
        return;
    }
    /*
        101010
        010101
        101010
        010101
        101010
        010101
        101010
    */
   k*=2;
    for(int i = 1; i <= 7; i++){
        for(int j = 1; j <= 6; j++){
            if(k){
                k--;
                if(i&1){
                    if(j&1){
                        cout << 1;
                    }else{
                        cout << 0;
                    }
                }else{
                    if(j&1){
                        cout << 0;
                    }else{
                        cout << 1;
                    }
                }
            }else{
                cout << 0;
            }
        }
        cout << endl;
    }
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