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
void solve() {
    int n, m; cin >> n >> m;
    string s; cin >> s;
    s = " " + s;
    int L = -1, R = -1;
    for(int i = 1; i <= n; i++) {
        if(s[i] == '?'){
            if(L == -1) L = i;
            R = i;
        }
    }
    if(L == -1){
        cout << s.substr(1) << endl;
        return;
    }

    int fl = 0, fr = 0;
    for(int i = 1; i <= n; i++) {
        if(i < L || i > R){
            if (s[i] == '(') fl++;
            else if (s[i] == ')') fr++;
        }
    }

    int c1 = n / 2 - fl;
    int c2 = n / 2 - fr;

    string ans = s;
    int cnt = 0;
    for(int i = 1; i < L; i++){
        if (s[i] == '(') cnt++;
        else cnt--;
    }

    int rem1 = c1, rem2 = c2;
    vii P;
    for(int i = L; i <= R; i++){
        if(rem2 > 0 && cnt > 0){
            ans[i] = ')';
            rem2--;
            cnt--;
        }else{
            ans[i] = '(';
            P.pb(i - L);
            rem1--;
            cnt++;
        }
    }
    int cn = 0, sum = 0;
    for(int i = 1; i <= n; i++) {
        if(ans[i] == '('){
            cn++;
        }else{
            sum += cn;
            cn--;
        }
    }

    int diff = m - sum;
    vii q(c1);
    for(int j = 0; j < c1; j++){
        int p = 0;
        if(j != 0) p = q[j-1] + 1;
        int x = min(diff, P[j] - p);
        q[j] = P[j] - x;
        diff -= x;
    }

    vector<int> vis(R - L + 1);
    for(int pos : q) {
        vis[pos] = 1;
    }
    for(int i = L; i <= R; i++){
        if(vis[i - L]) s[i] = '(';
        else s[i] = ')';
    }
    cout << s.substr(1) << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T = 1;
    if (cin >> T) {
        while (T--) solve();
    }
    return 0;
}