#include<bits/stdc++.h>
using namespace std;
#define rep(i, l, r) for (int i = l; i <= r; i++)
#define vii vector<int>
#define pii pair<int, int>
#define int long long
#define pb push_back
#define fi first
#define se second
// #define endl '\n'
double pi = acos(-1);
const int N = 1e6, mod = 1e9+7, inf = 1e18 + 5;
bool query(int i, int j) {
    if (i == j) return true; 
    cout << "? " << i << " " << j << endl; 
    string s; cin >> s;
    return s == "Yes";
}
void solve(){
    int n; cin >> n;
    int ans = 0;
    int r = 1;
    for(int l = 1; l < n; l++){
        if(r < l) r = l;
        while(r+1 <= n){
            if(query(l,r+1)){
                r++;
            }else{
                break;
            }
        }
        ans += r-l;
    }
    cout << "! " << ans << endl;
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