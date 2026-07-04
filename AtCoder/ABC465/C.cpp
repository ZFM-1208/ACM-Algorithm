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
    string s;
    cin >> s;
    s = " " + s;
    vector<int> p;
    p.pb(0);
    for(int i = 1; i <= n; i++){
        if(s[i] == 'o') p.push_back(i);
    }
    int nn = p.size();
    nn--;
    vector<int> ans;
    for(int i = nn; i >= 1; i--){
        int cnt = nn - i + 1;
        if(cnt & 1){
            for(int j = p[i]; j >= p[i - 1] + 1; j--){
                ans.pb(j);
            }
        }
    }
    for(int i = 1; i <= nn; i++){
        int cnt = nn - i + 1;
        if(cnt % 2 == 0){
            for(int j = p[i - 1] + 1; j <= p[i]; j++){
                ans.pb(j);
            }
        }
    }
    for(int i = p[nn] + 1; i <= n; i++){
        ans.pb(i);
    }
    for(int x: ans) cout << x << " ";
    cout << endl;
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