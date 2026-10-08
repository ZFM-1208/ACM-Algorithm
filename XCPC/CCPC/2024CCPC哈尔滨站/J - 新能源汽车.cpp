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
    vii a(n+1),cur(n+1);
    vector<vii> st(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        cur[i] = a[i];
    }
    vii X(m+1),T(m+1);
    for(int i = 1; i <= m; i++){
        cin >> X[i] >> T[i];
        st[T[i]].pb(X[i]);
    }
    priority_queue<pii, vector<pii>, greater<pii>> pq; // [位置, 类型]
    for(int i = 1; i <= n; i++){
        if(st[i].size() == 0) pq.push({inf, i});
        else pq.push({st[i][0],i});
    }
    int cur_pos = 0;
    vii ptr(n+1);
    for(int i = 1; i <= m; i++){
        int tar_pos = X[i];
        int c = T[i];
        int need = tar_pos - cur_pos;
        while(need){
            if(pq.size() == 0){
                for(int j = 1; j <= n; j++){
                    cur_pos += cur[j];
                }
                cout << cur_pos << endl;
                return;
            }
            auto [nxt_pos, cc] = pq.top();
            pq.pop();
            int rpos = (ptr[cc] < st[cc].size()) ? st[cc][ptr[cc]] : inf;
            if(nxt_pos != rpos) continue; 
            int mn = min(need, cur[cc]);
            cur[cc] -= mn;
            need -= mn;
            cur_pos += mn;
            if(cur[cc]) pq.push({rpos,cc});
        }
        cur[c] = a[c];
        ptr[c]++;
        if(ptr[c] < st[c].size()) pq.push({st[c][ptr[c]], c});
        else pq.push({inf,c});
    }
    for(int i = 1; i <= n; i++){
        cur_pos += cur[i];
    }
    cout << cur_pos << endl;

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