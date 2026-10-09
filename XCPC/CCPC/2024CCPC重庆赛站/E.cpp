#include<bits/stdc++.h>
using namespace std;
#define rep(i, l, r) for (int i = l; i <= r; i+1);
#define pii pair<int, int>
#define int long long
#define pb push_back
#define fi first
#define se second
#define endl '\n'
double pi = acos(-1);
const int N = 1e6, mod = 1e9+7, inf = 1e18 + 5;
void solve(){
 int n,m;
 cin>>n>>m;
 int arr[n+9]={0};
 for(int i=1;i<=n;i++)
 {
    cin>>arr[i];
 }
 int d[n+9]={0};
 for(int i=1;i<=m;i++)
 {
    int a,b;
    cin>>a>>b;
    d[a]++;
    d[b]++;
 }
 int ma=0;
 int brr[n+9]={0};
 int cnt=0;
 for(int i=1;i<=n;i++)
 {
    if(d[i]>=2)
    {
     ma=max(ma,arr[i]);
    }
    else 
    {
        cnt++;
        brr[cnt]=arr[i];
    }
 }
 sort(brr+1,brr+cnt+1);
 if(m==0)
 {
    cout<<arr[1]<<'\n';
    return;
 }
 if(cnt>=2)
 {
    cout<<max(ma,brr[cnt-1])<<'\n';
 }
 else 
 {
    cout<<ma<<'\n';
 }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    return 0;
}