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
/*
    由于允许精度误差，我们构造一个完全二分图，分成A,B两部分每组 n 个点，总点数 2n
    组与组之间都满足 距离近似1
    组内点都不满足

    构造双平行平面 z=0 和 z=1
    跨组点空间距离 = sqrt(d^2 + 1)，d为xy平面投影距离
    要求距离 < 1+ε=1.01，推导得 d < sqrt(2ε+ε²) ≈ 0.1418
    同组点要求两两距离 > ε=0.01，且同组距离远小于 1-ε=0.99，不会被计入近邻

    用10x10正方形网格排布，步长0.011（>0.01）
    10个点共9个间隔，最大跨度 9*0.011=0.099
    对角线最大投影距离 0.099*√2 ≈ 0.14 < 0.1418，满足跨组距离要求
    可容纳 n≤100 个点，完全覆盖题目范围
*/
void solve(){
    int n; cin >> n;
    cout << 2*n << endl;
    double d = 0.011;
    for(int i = 0; i < n; i++){
        double x = i % 10 * d;
        double y = i / 10 * d;
        cout << x << " " << y << " 0.0" << endl;
    }
    for(int i = 0; i < n; i++){
        double x = i % 10 * d;
        double y = i / 10 * d;
        cout << x << " " << y << " 1.0" << endl;
    }
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