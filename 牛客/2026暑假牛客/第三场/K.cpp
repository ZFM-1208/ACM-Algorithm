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
    vii x(n+1),y(n+1);
    for(int i = 1; i <= n; i++){
        cin >> x[i] >> y[i];
    }
    for(int i = 3; i <= n; i++){
        int x1 = x[i-1]-x[i-2], y1 = y[i-1]-y[i-2];
        int x2 = x[i]-x[i-1], y2 = y[i]-y[i-1];
         
        int cha = x1*y2-x2*y1;
        if(cha>0)cout<<"LEFT ";
        else if(cha)cout<<"RIGHT ";
        else cout<<"STRAIGHT ";
    }
    cout<<'\n';
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