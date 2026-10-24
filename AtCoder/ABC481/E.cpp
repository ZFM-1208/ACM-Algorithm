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
struct point{
    int x,y;
};
bool cmp(const point& a, const point& b){
    auto check = [&](const point& p) -> int {
        if(p.y > 0 || (p.x > 0 && p.y == 0)) return 0;
        return 1;
    };
    int aa = check(a);
    int bb = check(b);
    if(aa == bb){
        // 用二维向量叉积 
        // a x b = a.x * b.y - a.y * b.x
        // 若 > 0，则a在b顺时针放心
        __int128_t cross = (__int128_t)a.x * b.y - (__int128_t)a.y * b.x;
        return cross > 0;
    }else{
        return aa < bb;
    }
}
void solve(){
    int n; cin >> n;
    vector<point> p(n+1);
    rep(i,1,n) cin >> p[i].x >> p[i].y;
    if(n <= 2){
        cout << n << endl;
        return;
    }
    sort(p.begin()+1, p.end(), cmp);
    vector<point> a(2*n+1);
    for(int i = 1; i <= 2*n; i++){
        a[i] = p[(i-1)%n+1];
    }
    int ans = 0;
    for(int l = 1, r = 1; l <= n; l++){
        if(r < l) r = l;
        while(r+1 < l + n){
            __int128 cross = (__int128)a[l].x * a[r + 1].y - (__int128)a[l].y * a[r + 1].x;
            if(cross > 0) r++;
            else break;
        }
        ans = max(ans, r-l+1);
    }
    cout << ans << endl;
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