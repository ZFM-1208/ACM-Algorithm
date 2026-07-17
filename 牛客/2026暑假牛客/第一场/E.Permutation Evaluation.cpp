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
    int n;
   cin>>n;
   int arr[n+9];
   int brr[n+9];
   brr[n]=0;
   for(int i=0;i<n;i++)
   {
    cin>>arr[i];
   }
   for(int i=n-1;i>=0;i--)
   {
    brr[i]=brr[i+1]+arr[i];
   }
   int cnt=0;
   for(int i=0;i<n;i++)
   {
    cnt+=brr[i+1]-arr[i]*(n-1-i);
   }
   cout<<cnt;
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