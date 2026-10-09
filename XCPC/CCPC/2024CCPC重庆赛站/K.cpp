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
    1101 
    1
    0
    4
    8

*/
int ksm(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a ;
        a = a * a ;
        b >>= 1;
    }
    return res;
}

void solve(){
    int n; cin >> n;
    string s1,s2; cin >> s1 >> s2;
    int n1 = 0, n2 = 0;
    int op = 1;
    for(int i = 0; i < n; i++){
        int c1 = s1[i] - '0';
        int c2 = s2[i] - '0';
        if(c1!=1&&c2!=1)
        {
            cout << "0\n";
            return;
        }
        // n1 = n1 + op * c1;
        // n2 = n2 + op * c2;
        // cout << n1 << " " << n2 << endl;
        // op *= 3;
    }
    cout << "1\n";
    return;
    // cout << n1 << " " << n2 << end/
    // a2[0] = {0, 0, 0, 0, 1, 0, 0, 0, 0};
    // a2[1] = {0, 0, 0, 1, 1, 1, 0, 0, 0};
    // a2[2] = {0, 0, 0, 0, 1, 0, 0, 0, 0};
    // a2[3] = {0, 1, 0, 0, 1, 0, 0, 1, 0};
    // a2[4] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    // a2[5] = {0, 1, 0, 0, 1, 0, 0, 1, 0};
    // a2[6] = {0, 0, 0, 0, 1, 0, 0, 0, 0};
    // a2[7] = {0, 0, 0, 1, 1, 1, 0, 0, 0};
    // a2[8] = {0, 0, 0, 0, 1, 0, 0, 0, 0};
    // vector<vii> a3(27,vii(27));
    // vector<pii> cun;
    // for(int i = 0; i < 27; i++){
    //     for(int j = 0; j < 27; j++){
    //         if((ksm(3,n-1) <= i && i < 2*ksm(3,n-1)) || (ksm(3,n-1) <= j && j < 2*ksm(3,n-1))) {
    //             a3[i][j] = a2[(i % ksm(3,n-1))][(j % ksm(3,n-1))];
    //             cout << a3[i][j] << " ";
    //             if(a3[i][j] == 1){
    //                 cun.pb({i,j});
    //             }
    //             // cout << i << " " << j << endl;
    //         }else{
    //             cout << 0 << " ";
    //         }
    //     }
    //     cout << endl;
    // }
    // for(auto [x,y]: cun){
    //     cout << x << " " << y << " ";
    //     string xx = "0",yy = "0";
    //     while(x){
    //         xx += (char)((x % 3)+'0');
    //         x/=3;
    //     }
    //     while(y){
    //         yy += (char)((y % 3)+'0');
    //         y/=3;
    //     }
    //     reverse(xx.begin(),xx.end());
    //     reverse(yy.begin(),yy.end());
    //     cout << xx << " " << yy << endl;
    // }
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