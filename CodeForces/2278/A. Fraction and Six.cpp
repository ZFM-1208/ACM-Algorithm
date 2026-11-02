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
    int n,m; cin >> n >> m;
    string s1,s2;
    cin >> s1 >> s2;
    if(n != m + 3){
        cout << "No\n";
        return;
    }
    string s;
    map<char,int> mp;
    for(char c: s2) mp[c]++;
    for(char c: s1){
        if(mp[c] == 0){
            mp[c]++;
        }else{
            mp[c]--;
        }
    }
    // for(auto&[x,c]: mp) cout << x << " " << c<< endl;
    int cnt = 0;
    for(auto&[x,c]: mp){
        // cout << x << " " << c<< endl;
        if(c > 0){
            
            if(x == 's' || x == 'i' || x == 'x' ){
                // cout << x << " ";
                cnt++;
            }else{
                cout << "No\n";
                return;                

            }            
        }

    }

    if(cnt == 3) cout << "Yes\n";
    else cout << "No\n";
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