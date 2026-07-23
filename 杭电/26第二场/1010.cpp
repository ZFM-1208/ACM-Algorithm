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
struct node {
    int gain;
    int len;
    int change;
    bool operator<(const node& other) const {
        return gain < other.gain;
    }
};
void solve(){
    int n,k; cin >> n >> k;
    string s; cin >> s;
    s = " " + s;
    int cnt = 0;
    int cnt0 = 0;
    vii cun;
    for(int i = 1; i <= n; i++){
        if(s[i] == '0'){
            cnt++;
            cnt0++;
        }else{
            if(cnt > 0) cun.pb(cnt);
            cnt = 0;
        }
    }
    k = min(k, cnt0);
    if(cnt) cun.pb(cnt);
    auto calc = [&](int nn) -> int {
        return 20 * nn + 5 * nn * (nn + 1) / 2;
    };
    auto cost = [&](int nn, int c) -> int {
        int res = 0;
        int duan = c + 1;
        int rem = nn - c;
        int q = rem / duan;
        int r = rem % duan;
        res = r * calc(q + 1) + (duan - r) * calc(q);
        return res;
    };
    int ans = 0;
    priority_queue<node> pq;
    for(int len : cun){
        ans += calc(len);
        int gain = cost(len, 0) - cost(len, 1);
        pq.push({gain, len, 0LL});
    }
    while(k--){
        node cur = pq.top();
        pq.pop();
        ans -= cur.gain;
        cur.change++;
        if(cur.change < cur.len){
            cur.gain = cost(cur.len, cur.change) - cost(cur.len, cur.change + 1);
            pq.push(cur);
        }
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