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
    string s; cin >> s;
    int n = s.size();
    int base = 0;
    int down = 0, up = 0;
    for(int i = 0; i < n; i++){
        if(i&1){
            if(s[i] == '2'){
                down++;
            }else if(s[i] == '1'){
                base--;
            }
        }else{
            if(s[i] == '2'){
                up++;
            }else if(s[i] == '1'){
                base++;
            }
        }
    }
    int L = base - down, R = base + up;
    if(n&1){
        if(L <= 1 && R >= 0){
            cout << 1 << endl;
        }else if(L > 1) cout << 2*L-1 << endl;
        else if(R < 0) cout << 1-2*R << endl;
    }else{
        if(L <= 0 && 0 <= R){
            cout << 0 << endl;
        }else if(L > 0){
            cout << 2*L << endl;
        }else{
            cout << 2*abs(R) << endl;
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