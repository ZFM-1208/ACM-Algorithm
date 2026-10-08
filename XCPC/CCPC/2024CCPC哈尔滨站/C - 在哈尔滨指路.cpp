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

char ch[N];
int a[N];
void solve(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>ch[i]>>a[i];
    }
    int m=2*n-1;
    cout<<m<<' '<<ch[1]<<'\n';
    char ch1=ch[1];
    for(int i=1;i<n;i++){
        cout<<"Z "<<a[i]<<'\n';
        if(ch1=='N'){
            if(ch[i+1]=='W') cout<<"L\n";
            else cout<<"R\n";
        }else if(ch1=='S'){
            if(ch[i+1]=='W') cout<<"R\n";
            else cout<<"L\n";
        }else if(ch1=='W'){
            if(ch[i+1]=='S') cout<<"L\n";
            else cout<<"R\n";
        }else{
            if(ch[i+1]=='N') cout<<"L\n";
            else cout<<"R\n";
        }
        ch1=ch[i+1];
    }
    cout<<"Z "<<a[n]<<'\n';
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