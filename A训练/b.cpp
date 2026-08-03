#include<bits/stdc++.h> 
using namespace std;
#define int long long
struct node{
    int x1,y1,x2,y2;
};
void ff(){
    int n; cin >> n;
    vector<int> ans(n+1);
    vector<node> a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i].x1 >> a[i].y1 >> a[i].x2 >> a[i].y2;
    }
    for(int i = 1; i <= n; i++){
        
        for(int j = 1; j <= n; j++)
        {
            int cnt = 0;
            if(j == i) continue;
            int x1 = a[i].x1;
            int y1 = a[i].y1;
            int x2 = a[i].x2;
            int y2 = a[i].y2;            
            int x3 = a[j].x1;
            int y3 = a[j].y1;
            int x4 = a[j].x2;
            int y4 = a[j].y2;
            if(y4 >= y1 && y4 <= y2){
                if(x4 >= x1 && x4 <= x2){
                    cnt = 1;
                }
                if(x3 >= x1 && x3 <= x2){
                    cnt = 1;
                }
                if(x3 <= x1 && x4 >= x2){
                    cnt = 1;
                }
            }
            if(y3 <= y2 && y3 >= y1){
                if(x4 >= x1 && x4 <= x2){
                    cnt = 1;
                }
                if(x3 >= x1 && x3 <= x2){
                    cnt = 1;
                }
                if(x3 <= x1 && x4 >= x2){
                    cnt = 1;
                }
            }
            if(x4 >= x1 && x4 <= x2){
                if(y4 >= y1 && y4 <= y2){
                    cnt = 1;
                }
                if(y3 >= y1 && y3 <= y2){
                    cnt = 1;
                }
                if(y3 <= y1 && y4 >= y2){
                    cnt = 1;
                }
            }
            if(x3 >= x1 && x3 <= x2){
                if(y4 >= y1 && y4 <= y2){
                    cnt = 1;
                }
                if(y3 >= y1 && y3 <= y2){
                    cnt = 1;
                }
                if(y3 <= y1 && y4 >= y2){
                    cnt = 1;
                }
            }            
            if(x3 <= x1 && y3 <= y1 && x4 >= x2 && y4 >= y2){
                cnt = 1;
            }
            if(cnt == 1) {
                ans[i]++;
                // cout << i << " " << j << endl;;
            }

        }
        
    }
    for(int i = 1; i <= n; i++){
        cout << ans[i] << " ";
    }
    cout << endl;
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