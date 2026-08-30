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
    int n, b;cin >> n >> b;    
    // vector<string> s(n + 1);
    // rep(i, 1, n) cin >> s[i];
    vii a(n + 1);
    rep(i, 1, n){
        string s; cin >> s;
        int op = 0;
        for(char c : s) op = (op << 1) | (c - '0');
        a[i] = op;
    }
    vii ans(b + 1);
    int cnt = 0;
    for(int k = 1; k <= b; k++) {
        // unordered_map<string, int> mp;
        vector<int> mp(1LL << (b - 1));
        for(int i = 1; i <= n; i++){
            int x = a[i];
            int nx = ((x >> ((b - k) + 1)) << (b - k)) | (x & ((1LL << (b - k)) - 1));
            // cout << nx << endl;
            if(mp[nx] == 1){
                ans[k]++;
                cnt++;
            }
            mp[nx]++;
            // char tp = s[i][k - 1];
            // s[i][k - 1] = '*';
            // if(mp[s[i]] == 1){
            //     ans[k]++;
            //     cnt++;
            // }
            // mp[s[i]]++;
            // s[i][k - 1] = tp;
        }
    }
    cout << cnt << endl;
    for(int k = 1; k <= b; k++) {
        cout << ans[k] << " \n"[k==b];
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