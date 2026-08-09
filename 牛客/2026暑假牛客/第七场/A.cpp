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
    int n; cin >> n;
    vii a(n+1);
    rep(i,1,n) cin >> a[i];
    const int FULL = (1LL << 30) - 1;
    int ans = 0;
    for(int bit = 29; bit >= 0; bit--)
    {
        // 当前位暂时不买,低位暂时全购买
        int buy = ans | ((1LL << bit) - 1);
        bool ok = 1;
        int pre = 0;
        for(int i = 1; i <= n; i++)
        {
            int x = a[i];
            int fixed = x & (FULL ^ buy);
            int mx = fixed | buy;
            int cur = inf;
            if(fixed >= pre) cur = fixed;
            else if(mx < pre){
                ok = 0;
                break;
            }else if((pre & (FULL ^ buy)) == fixed){ // 判断pre本身是否可达
                cur = pre;
            }else { // fixed < pre <= mx
                int best = inf;
                bool same = 1;
                for(int bt = 29; bt >= 0; bt--)
                {
                    int pre_bit = (pre >> bt) & 1;
                    int fixed_bit = (fixed >> bt) & 1;
                    int buy_bit = (buy >> bt) & 1;    
                    bool can = buy_bit || fixed_bit;
                    if(same && pre_bit == 0 && can)
                    {
                        // bt 以下全部位置
                        int lower = (1LL << bt) - 1;
                        /*
                            bt 以上复制 pre。

                            ((1LL << (bt + 1)) - 1) 的第 0 到 bt 位全为 1。

                            用 FULL 异或后， 只保留 bt 以上的位置。
                        */
                        int high = pre & (FULL ^ ((1LL << (bt + 1)) - 1));
                        int op = high | (1LL << bt) | (fixed & lower);
                        best = min(best, op);
                    }       
                    if(buy_bit == 0 && fixed_bit != pre_bit){
                        same = false;
                    }          
                }
                if(best == inf){
                    ok = false;
                    break;
                }
                cur = best;
            }
            pre = cur;
        }
        if(ok == 0){
            ans |= (1LL << bit);
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