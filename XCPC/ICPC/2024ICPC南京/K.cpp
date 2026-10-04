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
/*
    【解题思路总结：分段贪心 + 余量统计 + 越界倒序回推】

    1. 黑格分段独立性：
    纸条不能覆盖黑格且长为 k，纸条两两互不重叠。
    因此在两端补上 0 和 w + 1 后，任意相邻两黑格 (L, R) 之间的可用开区间 [L + 1, R - 1] 相互完全独立，可单独求解。

    2. 预处理红格段：
    将落在 [L + 1, R - 1] 内的所有连续红格预处理为若干个不相交的极大闭区间 [l, r]。

    3. 正向贪心与余量统计（以最左极限靠拢）：
    维护已覆盖的最右位置 fg（初始为 L）和可左移压缩的白格总数 sum（余量）。
    遍历红格段，若当前红段有未覆盖部分（起点为 st = max(l, fg + 1)）：
    - 该起点与上一覆盖端点之间的白格数 (st - fg - 1) 计入缓冲余量 sum。
    - 放置长为 k 的纸条 [st, st + k - 1]：
        * 若未越界 (st + k - 1 < R)：直接存入该纸条位置，更新 fg = st + k - 1，继续向后。
        * 若越界 (st + k - 1 >= R)：触发回推流程。

    4. 越界倒序回推：
    - 合法性校验：总越界量为 (st + k - 1) - (R - 1)。若 sum < 越界量，说明即使前面所有纸条无缝死死贴合也塞不下，判定无解输出 -1。
    - 连锁回推：
        * 将最后一张纸条强行贴齐右边界（右端点设为 xg = R - 1，左端点置为 xg - k + 1）。
        * 从后向前遍历前驱纸条：若前驱纸条自然右端点 >= xg（与当前纸条重叠），则将前驱纸条也紧贴着向左推平，更新新的 xg；一旦不重叠则 break 终止回推。
    - 倒推完成后直接 break 退出当前黑格区间。

    5. 收集并输出所有区间的纸条放置方案。
*/
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
        vii jl;
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
            while(cr > fg){
                int st = max(cl, fg + 1);
                sum += (st - fg - 1);
                if(st + k - 1 < R){
                    // 没撞上，直接放置
                    jl.pb(st);
                    fg = st + k - 1;
                }else {
                    /*
                                          R      
                        1  2  3  4  5  6  7  8  9 
                        st   
                        [                       ]  
                    
                    */
                    if(sum >= (st + k - 1) - (R - 1)){
                        jl.pb(st);
                        int xg = R - 1; 
                        for (int kk = jl.size() - 1; kk >= 0; kk--){
                            if(jl[kk] + k - 1 < xg){
                                break; 
                            }else {
                                jl[kk] = xg - k + 1; 
                                xg = jl[kk] - 1;
                            }
                        }
                        ok = true;
                    }else {
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