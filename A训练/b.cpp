#include <bits/stdc++.h>
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
const int N = 1e6, mod = 1e9 + 7, inf = 1e18 + 5;
int n, k, m, q;
struct node{
    int l,r,len;
};
struct node1{
    int l,r,id;
};

struct BIT_premax{
    int n;
    vector<int> tr;
    BIT_premax(int _n) :n(_n), tr(_n+1, 0){};
    int lowbit(int x) {return x & -x;}
    void update(int x, int c){
        for(int i = x; i <= n; i += lowbit(i))
            tr[i] = max(tr[i], c);
    }
    int query(int x){
        int res = 0;
        for(int i = x; i > 0; i -= lowbit(i))
            res = max(res,tr[i]);
        return res;
    }
};
void solve()
{
    int n,q; cin >> n >> q;
    vector<int> ydd;
    vector<node> a(n+1);
    vector<node1> qs(q+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i].l >> a[i].r;
        a[i].len = a[i].r - a[i].l + 1;
        ydd.pb(a[i].r);
    }
    for(int i = 1; i <= q; i++){
        cin >> qs[i].l >> qs[i].r;
        qs[i].id = i;
        ydd.pb(qs[i].r);
    }
    sort(ydd.begin(),ydd.end());
    ydd.erase(unique(ydd.begin(), ydd.end()),ydd.end());
    sort(a.begin()+1,a.end(),[](auto x, auto y){
        return x.l > y.l;
    });
    sort(qs.begin()+1,qs.end(),[](auto x, auto y){
        return x.l > y.l;
    });    
    for(int i = 1; i <= n; i++){
        a[i].r = lower_bound(ydd.begin(), ydd.end(), a[i].r) - ydd.begin() + 1;
    }
    for(int i = 1; i <= q; i++){
        qs[i].r = lower_bound(ydd.begin(), ydd.end(), qs[i].r) - ydd.begin() + 1;
    }
    vector<int> cun;
    int pr = 1;
    BIT_premax bit(n+q+1);
    vector<int> ans(q+1);
    for(int i = 1; i <= q; i++){
        while(pr <= n && a[pr].l >= qs[i].l){
            bit.update(a[pr].r, a[pr].len);
            pr++;
        }
        int res = bit.query(qs[i].r);
        ans[qs[i].id] = res;
    }
    for(int i = 1; i <= q; i++){
        cout << ans[i] << endl;
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}