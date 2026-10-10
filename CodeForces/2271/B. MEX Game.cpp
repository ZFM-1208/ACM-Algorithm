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
    int n,k; cin >> n >> k;
    vii cnt(n+2);
    for(int i = 1; i <= n; i++){
        int x; cin >> x;
        cnt[x]++;
    }
    int op = 0;
    for(int i = 0; i <= n; i++){
        if(cnt[i] < 2*k){
            op = i;
            break;
        }
    }
    if(cnt[op] == 2*k-1){
        cout << "YES" << endl;
    }else{
        cout << "NO" << endl;
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