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

void solve(){
    int n, m, k, w;
    cin >> n >> m >> k >> w;
    vii a(n + 1);
    rep(i, 1, n) cin >> a[i];
    vii b(m + 1);
    rep(i, 1, m) cin >> b[i];
    sort(a.begin() + 1, a.end());
    b.pb(0);
    b.pb(w + 1);
    sort(b.begin() + 1, b.end());
    m += 2;
    vii ans;
    int op = 1;
    for (int i = 1; i < m; i++){
        int L = b[i], R = b[i + 1];
        // [L+1, R-1]
        vector<pii> cun;
        while(op <= n && a[op] < R){
            int l = a[op];
            int r = a[op];
            while(op + 1 <= n && a[op + 1] < R && a[op + 1] == r + 1){
                r = a[op + 1];
                op++;
            }
            op++;
            cun.pb({l, r});
        }
        if(cun.empty()) continue;
        vii jl;        // 记录本黑格区间内每张纸条的左端点
        int fg = L;    
        int sum = 0;    
        bool ok = 0;
        for(auto &[cl, cr] : cun){
            // if(fg >= cr) continue;
            /*
                cl                      cr
                1  2  3  4  5  6  7  8  9
                   fg [                 ]

                        [cl            cr]
                1  2  3  4  5  6  7  8  9
                fg *  *
            
            */
            while (cr > fg){
                int st = max(cl, fg + 1);
                sum += (st - fg - 1);
                if(st + k - 1 < R)
                {
                    // 没撞上，直接放置
                    jl.pb(st);
                    fg = st + k - 1;
                }
                else
                {
                    // 撞上了右黑块，计算超出 R 的越界量
                    int over = (st + k - 1) - (R - 1);
                    if (sum >= over)
                    {
                        // 余量够用，新纸条压入后从右向左推移
                        jl.pb(st);
                        int xg = R - 1; // 从右黑格前一位倒着排

                        for (int kk = (int)jl.size() - 1; kk >= 0; kk--)
                        {
                            if (jl[kk] + k - 1 < xg)
                            {
                                break; // 不发生重叠，停止推移
                            }
                            else
                            {
                                jl[kk] = xg - k + 1; // 贴紧排布
                                xg = jl[kk] - 1;
                            }
                        }
                        ok = true;
                    }
                    else
                    {
                        // 积累的空隙不够吸收越界，无解
                        cout << -1 << endl;
                        return;
                    }
                    break;
                }
            }
            if (ok) break;
        }
        for (int x : jl) ans.pb(x);
    }
    cout << ans.size() << endl;
    for(int x: ans) cout << x << " ";
    cout << endl;
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