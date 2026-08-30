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
    int q; cin >> q;
    vector<array<int, 2>> tr(25*q);
    vii mp(25*q);
    int cnt = 0, ans = 0;
    while (q--) {
        char op; cin >> op;
        string s; cin >> s;
        int now = 0;
        if(op == '+'){
            for(char ch : s){
                if(!tr[now][ch - '0']){
                    tr[now][ch - '0'] = ++cnt;
                }
                now = tr[now][ch - '0'];
                if(mp[now] == 0){
                    ans++;
                }
                mp[now]++;
            }
        }else{
            for(char ch : s){
                now = tr[now][ch - '0'];
                mp[now]--;
                if(mp[now] == 0) {
                    ans--;
                }
            }
        }
        cout << ans << endl;
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