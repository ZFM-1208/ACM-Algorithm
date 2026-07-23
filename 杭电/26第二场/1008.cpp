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
    vector<vii> mp(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        mp[a[i]].push_back(i);
    }

    sort(a.begin()+1, a.end());
    if(a[n] > 2 * a[1] - 1){
        cout << "No" << endl;
        return;
    }
    for(int i = a[2]; i <= a[n]; i++){
        if(mp[i].size() < 2){
            cout << "No" << endl;
            return;
        }
    }
    if(n == 1){
        if(a[1] != 1){
            cout << "No" << endl;
        }else{
            cout << "Yes" << endl;
        }
        return;
    }
    if(n == 2){
        if(a[1] != 2 || a[2] != 2){
            cout << "No" << endl;
        }else{
            cout << "Yes" << endl;
            cout << 1 << " " << 2 << endl;
        }
        return;
    }  
    if(mp[a[1]].size() == 1){
        if(a[n] != 2 * a[1] - 1){
            cout << "No" << endl;
            return;
        }
        cout << "Yes" << endl;
        for(int i = a[2]; i <= a[n]; i++){
            cout << mp[i-1][0] << " " << mp[i][0] << endl;
        }
        for(int i = a[2]; i <= a[n]; i++){
            if(i == a[2]){
                cout << mp[i-1][0] << " " << mp[i][1] << endl;
            }else{
                cout << mp[i-1][1] << " " << mp[i][1] << endl;
            } 
        }
        for(int i = a[2]; i <= a[n]; i++){
            for(int j = 2; j < mp[i].size(); j++){
                cout << mp[i][j] << " " << mp[i-1][0] << endl;
            }
        }
    }else if(mp[a[1]].size() == 2){
        if(a[n] != 2 * (a[1] - 1)){
            cout << "No" << endl;
            return;
        }
        cout << "Yes" << endl;
        cout << mp[a[1]][0] << " " << mp[a[1]][1] << endl;
        for(int i = a[3]; i <= a[n]; i++){
            cout << mp[i-1][0] << " " << mp[i][0] << endl;
        }
        for(int i = a[3]; i <= a[n]; i++){
            cout << mp[i-1][1] << " " << mp[i][1] << endl;
        }
        for(int i = a[3]; i <= a[n]; i++){
            for(int j = 2; j < mp[i].size(); j++){
                cout << mp[i][j] << " " << mp[i-1][0] << endl;
            }
        }
    }else{
        cout << "No" << endl;
        return;        
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