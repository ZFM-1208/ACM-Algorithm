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
vector<int>su;
void init(){
    for(int i = 1; i <= N; i++){
        bool ok = 0;
        for(int j = 2; j * j <= i; j++){
            if(i % j == 0){
                ok = 1;
                break;
            }
        }
        if(ok == 0) su.push_back(i);
    }
}
void solve(){
    int n; cin >> n;
    vector<int> a(n+1);
    unordered_map<int, vector<int>> mp;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        mp[a[i]].pb(i);
    }
    vector<vii> adj(n+1);
    for(int p: su){
        for(int i = )
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T = 1;
    init();
    cin >> T;
    while(T--)
        solve();
    return 0;
}