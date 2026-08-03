#include<bits/stdc++.h> 
using namespace std;
#define int long long
const int inf = 1e18;
void ff(){
    int n; cin >> n;
    string s; cin >> s;
    s = " " + s;
    vector<int> a(n+1);
    int ans = 0;
    vector<int> pre(n+1),prea(n+1);
    
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        ans += a[i];
        pre[i] = pre[i-1] + a[i];
    }
    vector<int> dp(n+1, -inf);
    dp[0] = 0;
    int cnta = 0; // a的个数
    vector<int> cun;
    vector<int> suma(n+1);
    int caa = 0;
    for(int i = 1; i <= n; i++){
        if(s[i] == 'a'){
            cun.push_back(i);
            cnta++;
            caa++;
            suma[i] = cnta;
        }else{
            cnta = 0;
            suma[i] = 0;
        }
        prea[i] = caa;
    }
    for(int i = 1; i <= n; i++){

        if(s[i] == 'a'){
            dp[i] = dp[i-1] + a[i];
        }else if(s[i] == 'b'){
            dp[i] = dp[i-1] + a[i];
            // 删
            int l = 0,r = cun.size() - 1;
            int p = -1;
            /*
                   p     i
                12345678910
                aaaababcbc

                4 <= 5 - 4
            */
            while(l <= r){
                int mid = (l + r) / 2;
                if(cun[mid] <= i){
                    p = mid;
                    l = mid + 1;
                }else{
                    r = mid - 1;
                }
            }
            // cout << "i: " << i << " p:" << p << endl;
            if(p != -1){
                if(suma[cun[p]] >= i - cun[p]){
                    dp[i] = max(dp[i], dp[i - 2 * (i - cun[p])]);
                }else{
                    int r = p - 1;
                    while(r >= 0){
                        if(suma[cun[r]] >= i - cun[r] - 2*(prea[i] + prea[cun[r]])){
                            break;
                        }
                        r--;
                    }
                    // cout << "i: " << i << " r:" << r << endl;
                    if(r >= 0){
                        dp[i] = max(dp[i], dp[i - 2 * (i - cun[r]) + 2*(prea[i] - prea[cun[r]]) ]);
                    }
                }
            }

        }else if(s[i] == 'c'){
            /*
                   p     i
                12345678910
                aaaababcbc

            */
        
            dp[i] = dp[i-1] + a[i];
            int l = 0,r = cun.size() - 1;
            int p = -1;
            while(l <= r){
                int mid = (l + r) / 2;
                if(cun[mid] <= i){
                    p = mid;
                    l = mid + 1;
                }else{
                    r = mid - 1;
                }
            }
            // cout << "i: " << i << " p:" << p << endl;
            // cout << cun[p] << endl;
            if(p != -1){
                
                if(suma[cun[p]] >= i - cun[p]){
                    // cout << "i: " << i << " p:" << p << endl;
                    dp[i] = max(dp[i], dp[i - 2 * (i - cun[p])]);
                }else{
                    int r = p - 1;
                    while(r >= 0){
                        // if(i == 10)
                        // cout << suma[cun[r]] << " " << i << " " << cun[r] << " " << prea[i] << " " << prea[cun[r]] << endl;
                        if(suma[cun[r]] >= i - cun[r] - 2*(prea[i] + prea[cun[r]])){
                            break;
                        }
                        r--;
                    }
                    // cout << "i: " << i << " r:" << r << endl;
                    if(r >= 0){
                        // cout << "LLLL";
                        // cout << i - 2 * (i - cun[r]) + 2*(prea[i] - prea[cun[r]]) << endl;
                        dp[i] = max(dp[i], dp[i - 2 * (i - cun[r]) + 2*(prea[i] - prea[cun[r]]) ]);
                    }
                }
            }
        }
    }
    // for(int i = 1; i <= n; i++){
    //     cout << dp[i] << " \n"[i==n];
    // }
    ans = max(ans, dp[n]);
    cout << ans << endl;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    while(T--){
        ff();
    }
    return 0;
}