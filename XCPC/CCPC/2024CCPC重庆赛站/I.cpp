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
const int N = 1e6, mod = 998244353, inf = 1e18 + 5;
void solve(){
 int arr[100]={0};
 for(int i=1;i<=9;i++)
 {
    cin>>arr[i];
 }
 if(arr[1]==0)
 {
    int t=1;
   for(int i=1;i<=9;i++)
   {
    for(int j=1;j<=arr[i];j++)
    {
        t=(t*i)%mod;
    }
   }
   cout<<t<<'\n';
 }
 else if(arr[2]==0)
 {
    int x=arr[1];
    while(arr[1]>=3)
    {
        arr[3]++;
        arr[1]-=3;
    }
    int xx=arr[1];
    arr[1]=0;
    arr[xx]++;
    if(arr[1]==0)
    {
        int t=1;
        for(int i=2;i<=9;i++)
        {
            for(int j=1;j<=arr[i];j++)
           {
        t=(t*i)%mod;
           }
        }
        cout<<t<<'\n';
        return;
    }
    else 
    {
        for(int i=2;i<=9;i++)
        {
            if(arr[i]!=0)
            {
                arr[i]--;
                arr[i+1]++;
                break;
            }
        }
        int t=1;
        for(int i=2;i<=10;i++)
        {
            for(int j=1;j<=arr[i];j++)
           {
             t=(t*i)%mod;
           }
        }
        cout<<t<<'\n';
        return;
    }
    
 }
 else 
 {
    int k=min(arr[2],arr[1]);
    arr[1]-=k;
    arr[2]-=k;
    arr[3]+=k;
    int x=arr[1];
    while(arr[1]>=3)
    {
        arr[3]++;
        arr[1]-=3;
    }
    int xx=arr[1];
    arr[1]=0;
    arr[xx]++;
    if(arr[1]==0)
    {
        int t=1;
        for(int i=2;i<=9;i++)
        {
            for(int j=1;j<=arr[i];j++)
           {
        t=(t*i)%mod;
           }
        }
        cout<<t<<'\n';
        return;
    }
    else 
    {
        for(int i=2;i<=9;i++)
        {
            if(arr[i]!=0)
            {
                arr[i]--;
                arr[i+1]++;
                break;
            }
        }
        int t=1;
        for(int i=2;i<=10;i++)
        {
            for(int j=1;j<=arr[i];j++)
           {
             t=(t*i)%mod;
           }
        }
        cout<<t<<'\n';
        return;
    }
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
// 1 1 1 1 2 3 4
// 3*3*3*2 
// 5*3*2*3