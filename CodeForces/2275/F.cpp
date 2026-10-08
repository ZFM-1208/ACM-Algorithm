#include<bits/stdc++.h>
using namespace std;
#define rep(i, l, r) for (int i = l; i <= r; i++)
#define vii vector<int>
#define pii pair<int, int>
// #define int long long
#define pb push_back
#define fi first
#define se second
#define endl '\n'
double pi = acos(-1);
const int N = 1e6, mod = 1e9+7, inf = 1e18+5;
vector<int> pri; 

void init() {
    vector<bool> su(N+10, true);
    su[0] = su[1] = false;
    for(int i = 2; i * i <= N; i++){
        if(su[i]){
            for(int j = i * i; j <= N; j += i){
                su[j] = false;
            }
        }
    }
    for(int i = 2; i <= N; ++i){
        if(su[i]) pri.push_back(i);
    }
}

void solve(){
    int n; cin >> n;
    vii a(n+1);
    vector<vii> cun(n+1); 
    
    auto get = [&](int x) -> vii {
        vii res;
        for(int p : pri){
            if((long long)p * p > x) break;
            if(x % p == 0){
                int cnt = 0;
                while(x % p == 0){
                    x /= p;
                    cnt++;
                }
                if(cnt & 1) res.pb(p);
            }
        }
        if(x > 1) res.pb(x);
        return res;
    };
    
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        cun[i] = get(a[i]);
    }
    
    vector<vii> c;
    for(int i = 1; i <= n; i++) c.pb(cun[i]);
    
    vii cur;
    for(int i = 1; i <= n; i++){
        vii tp;
        int l = 0, r = 0;
        while(l < (int)cur.size() && r < (int)cun[i].size()){
            if(cur[l] < cun[i][r]) {
                tp.pb(cur[l++]);
            } else if(cur[l] > cun[i][r]){
                tp.pb(cun[i][r++]);
            } else {
                l++; r++;
            }
        }
        while(l < (int)cur.size()) tp.pb(cur[l++]);
        while(r < (int)cun[i].size()) tp.pb(cun[i][r++]);
        cur = move(tp);
        c.pb(cur);
    }
    
    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()), c.end());
    
    vector<int> cnt(c.size());
    for(int i = 1; i <= n; i++){
        int id = lower_bound(c.begin(), c.end(), cun[i]) - c.begin();
        cnt[id]++;
    }
    
    long long ans = 0;
    cur.clear();
    for(int i = 1; i <= n; i++){
        vii tp;
        int l = 0, r = 0;
        while(l < (int)cur.size() && r < (int)cun[i].size()){
            if(cur[l] < cun[i][r]) {
                tp.pb(cur[l++]);
            } else if(cur[l] > cun[i][r]){
                tp.pb(cun[i][r++]);
            } else {
                l++; r++;
            }
        }
        while(l < (int)cur.size()) tp.pb(cur[l++]);
        while(r < (int)cun[i].size()) tp.pb(cun[i][r++]);
        cur = move(tp);
        int id = lower_bound(c.begin(), c.end(), cur) - c.begin();
        ans += cnt[id];
    }
    cout << ans << endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T = 1;
    cin >> T;
    init();
    while(T--)
        solve();
    return 0;
}