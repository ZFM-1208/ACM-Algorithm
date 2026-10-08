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
struct node{
    int w,l,r;
};
void solve(){
    int n,m; cin >> n >> m;
    vector<node> a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i].w >> a[i].l >> a[i].r;
    }
    sort(a.begin()+1,a.end(),[](auto x, auto y){
        return x.w < y.w;
    });
    int ans = 0;
    int sum = m;
    for(int i = 1; i <= n; i++){
        ans += a[i].l * a[i].w;
        sum -= a[i].l;
    }
    // ans += sum * a[n].w;
    vector<int> b(n+2);
    vector<int> suf(n+2);
    vector<int> sj(n+2);
    for(int i = n; i >= 1; i--){
        b[i] = a[i].w * (a[i].r - a[i].l);
        suf[i] = suf[i + 1] + b[i];
        sj[i] = sj[i+1] + (a[i].r - a[i].l);
    }
    int op = ans;
    for(int i = 1; i <= n; i++){
        int tot = sum + a[i].l;
        int l = i, r = n;
        int p = n+1;
        int tp = sj[i];
        sj[i] = m+1;
        while(l <= r){
            int mid = (l + r) / 2;
            if(sj[mid] <= tot){
                p = mid;
                r = mid - 1;
                
            }else{
                l = mid + 1;
            }
        }
        // cout << "y: " << tot - sj[p] << endl;
        int res = op - a[i].w * a[i].l + suf[p] + a[max(p-1,i)].w * (tot - sj[p]);
        // cout << p << " ";
        // cout << res << endl;
        ans = max(ans, res);   
        sj[i] = tp;
    }
    cout << ans << endl;
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