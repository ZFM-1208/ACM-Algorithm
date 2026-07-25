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
    n个队伍,m次提交,k台评测鸡
    第i次提交: 属于队伍ai,在bi提交,评测需要ci秒  (bi递增)
    <1>: 一台评测机同时只能评测一份提交
    <2>: 同一支队伍同时最多只能有一份提交正在评测
    <3>: 当存在空闲评测机时，从所有“队伍当前没有正在评测”的等待提交中，选择提交时间最早的开始评测；
    <4>: 如果提交在 T 时刻开始，结束时刻为 T + ci
    <5>: 同一时刻的“提交到达”和“评测结束”全部发生后，再统一调度
    ==>  要求输出每份提交实际开始评测的时刻
*/

/*
    bi,ci <= 1e9;  不能按秒模拟
    只有当 有新的提交 / 运行的提交评测结束 时状态才会变化
    so: 只用依次处理这些 事件时刻
    离散事件模拟

*/

void solve(){
    
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