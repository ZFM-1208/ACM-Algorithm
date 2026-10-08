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
const int N = 1e6, mod = 1e9+7, inf = 8e18; 
using i128 = __int128_t;
struct Point {
    int x, y, id;
    Point(int x = 0, int y = 0, int id = 0) : x(x), y(y), id(id) {}
    Point operator-(const Point& o) const { return Point(x - o.x, y - o.y); }
    Point operator+(const Point& o) const { return Point(x + o.x, y + o.y); }
    bool operator<(const Point& o) const { return x < o.x || (x == o.x && y < o.y); }
    bool operator==(const Point& o) const { return x == o.x && y == o.y; }
};

int Cross(Point a, Point b) {
    return (int)((i128)a.x * b.y - (i128)a.y * b.x);
}

int ConvexHull(Point* p, int n, Point* ch){
    sort(p, p + n);
    int m = 0;
    for(int i = 0; i < n; i++){
        while(m > 1 && Cross(ch[m-1] - ch[m-2], p[i] - ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    int k = m;
    for(int i = n - 2; i >= 0; i--){
        while(m > k && Cross(ch[m-1] - ch[m-2], p[i] - ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    if(n > 1) m--;
    return m;
}

void solve(){
    int n; 
    cin >> n;
    vector<Point> p(n);
    for(int i = 0; i < n; i++){
        cin >> p[i].x >> p[i].y;
        p[i].id = i;
    }
    if(n == 3){
        cout << -1 << endl;
        return;
    }
    vector<Point> ch(2 * n);
    int m = ConvexHull(p.data(), n, ch.data());
    if(m == n){
        cout << -1 << endl;
        return;
    }
    int ans = 0;
    for(int i = 1; i < m - 1; i++){
        ans += Cross(ch[i] - ch[0], ch[i+1] - ch[0]);
    }
    ans = abs(ans);
    vector<bool> on_hull(n, false);
    for(int i = 0; i < m; i++){
        on_hull[ch[i].id] = true;
    }
    vector<Point> inner;
    for(int i = 0; i < n; i++){
        if(!on_hull[p[i].id]){
            inner.pb(p[i]);
        }
    }
    int k_in = inner.size();
    int mn = inf;

    if(k_in < 3){
        for(int i = 0; i < m; i++){
            Point e = ch[(i + 1) % m] - ch[i];
            for(int t = 0; t < k_in; t++){
                int cur = Cross(e, inner[t] - ch[i]);
                mn = min(mn, cur);
            }
        }
        cout << ans - mn << endl;
        return;
    }

    vector<Point> q(2 * k_in);
    int k = ConvexHull(inner.data(), k_in, q.data());

    int j = 0;
    Point e0 = ch[1] - ch[0];
    for(int t = 1; t < k; t++){
        if(Cross(e0, q[t] - ch[0]) < Cross(e0, q[j] - ch[0])){
            j = t;
        }
    }
    for(int i = 0; i < m; i++){
        Point e = ch[(i + 1) % m] - ch[i];
        while(Cross(e, q[(j + 1) % k] - ch[i]) < Cross(e, q[j] - ch[i])){
            j = (j + 1) % k;
        }
        int cur = Cross(e, q[j] - ch[i]);
        mn = min(mn, cur);
    }
    cout << ans - mn << endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();
    return 0;
}