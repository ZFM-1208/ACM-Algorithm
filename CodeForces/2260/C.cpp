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
    int x, y; cin >> x >> y;
    cout << x + y << " ";
    int mx = 0; 
    if((x & (x + y)) == x){
        cout << 0 << endl;
        return;
    }
    for(int i = 29; i >= 0; i--){
        if((x >> i) & 1LL){
            int tp = 0;
            for(int j = 29; j > i; j--){
                if((x >> j) & 1LL){
                    tp |= (1LL << j);
                }
            }
            for(int j = i - 1; j >= 0; j--){
                if(((x + y) >> j) & 1LL){
                    tp |= (1LL << j);
                }
            }
            mx = max(mx, tp);
        }
        if(((x >> i) & 1LL) && (!(((x + y) >> i) & 1LL))){
            break;
        }
    }
    cout << x - mx << endl;
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