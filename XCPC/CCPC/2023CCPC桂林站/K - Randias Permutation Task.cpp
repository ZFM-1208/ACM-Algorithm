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
    int n,m; cin >> n >> m;
    vector<vii> a(m+1,vii(n+1));
    rep(i,1,m) rep(j,1,n) cin >> a[i][j];
    auto get = [&](const vii& arr, const vii& brr) -> vii {
        vii c(n+1);
        rep(i,1,n) c[i] = arr[brr[i]];
        return c;
    };
    set<vii> st;
    // set 维护 : 仅使用前 i - 1 个排列的所有非空子序列，所能复合出的所有本质不同排列
    for(int i = 1; i <= m; i++){
        vector<vii> add;
        add.pb(a[i]);
        for(const auto& p: st){
            add.pb(get(p,a[i]));
        }
        for(const auto& p: add){
            st.insert(p);
        }
    }
    cout << st.size() % mod << endl;

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