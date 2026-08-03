#include<bits/stdc++.h> 
using namespace std;
#define int long long
vector<int>su;
void ff(){
    for(int i = 1; i <= 1000000; i++){
        bool ok = 0;
        for(int j = 2; j * j <= i; j++){
            if(i % j == 0){
                ok = 1;
                break;
            }
        }
        if(ok == 0) su.push_back(i);
    }
    for(auto x: su) {
        cout << x << ",";
    }
    // int n; cin >> n;
    // int ans = 0;
    // if(n&1){
    //     ans = n * (n / 2);
    //     if(n % 6 == 3){
    //         ans -= (n - n / 3);
    //     }
    //     cout << ans << endl;
    // }else{
    //     int tp = n/2;

    //     if(tp & 1){
    //         int cn = 0;
    //         cn = n / 2 / 2;
    //         ans = 2 * n * cn; 
    //     }else{
    //         int cn = 0;
    //         cn = n / 2 / 2;
    //         ans = 2 * n * cn; 
    //         ans -= n;
    //     }
    //     if(n % 6 == 0) {
    //         ans -= (n - n / 3);  
    //     }          
    //     cout << ans << endl;
    // }
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >> T;
    while(T--){
        ff();
    }
    return 0;
}