#include<bits/stdc++.h>
using namespace std;
#define rep(i, l, r) for (int i = l; i <= r; i++)
#define vii vector<int>
#define pii pair<int, char>
#define int long long
#define pb push_back
#define fi first
#define se second
#define endl '\n'
double pi = acos(-1);
const int N = 1e6, mod = 1e9+7, inf = 1e18 + 5;
/*
    牌面点数：
    A 2 3 4 5 6 7 8 9 T J Q K
 
    炒鸡同花顺 10 
    同花顺     9
    4+1        8
    3+2        7
    同花       6
    顺子       5
    3+1+1      4
    2+2+1      3
    2+1+1+1    2
    烂牌       1
 
*/
void solve(){
    vector<pair<int,char>> s(9);
    auto get = [](string s) -> pii {
        int x;
        if(s[0]=='T') x = 10;
        else if(s[0]=='J') x = 11;
        else if(s[0]=='Q') x = 12;
        else if(s[0]=='K') x = 13;
        else if(s[0]=='A') x = 14;
        else x = s[0] - '0';
        return {x, s[1]};
    };
    for(int i = 1; i <= 8; i++){
        string ts; cin >> ts;
        s[i] = get(ts);
    }
    vector<pair<int,char>> cun;
    string color = "CDHS";
    for(int i = 2; i <= 14; i++){
        for(auto &c : color) cun.pb({i,c});
    }
    vector<bool> vis(52);
    for(int i = 1; i <= 8; i++){
        for(int j = 0; j < 52; j++){
            if(cun[j] == s[i]) vis[j] = 1;
        }
    }

    auto get1 = [](vector<pair<int,char>> a){
        array<int,6> ret = {0};
        unordered_map<int,int> cnt;
        vector<int> b;
        for(auto &[x,y] : a){
            cnt[x]++;
            b.pb(x);
        }
        int th = 1;
        for(int i = 1; i < 5; i++){
            if(a[i].second != a[0].second){
                th = 0;
                break;
            }
        }
        sort(b.begin(), b.end());
        int sh = 0;
        if(b == vector<int>{2,3,4,5,14}) sh = 5;
        else{
            int ok = 1;
            for(int i = 1; i < 5; i++){
                if(b[i] != b[i-1] + 1){
                    ok = 0;
                    break;
                }
            }
            if(ok) sh = b[4];
        }
        /* 超级同花顺/同花顺 */
        if(th && sh){
            if(sh == 14 && b[0] == 10){
                ret[0] = 10;
                ret[1] = 14;
            }
            else{
                ret[0] = 9;
                ret[1] = sh;
            }
            return ret;
        }
        int four = 0, three = 0;
        vector<int> tok;
        int one = 0;
        for(int i = 2; i <= 14; i++){
            if(cnt[i] == 4) four = i;
            else if(cnt[i] == 3) three = i;
            else if(cnt[i] == 2) tok.pb(i);
            else if(cnt[i] == 1) one = i;
        }
         /* 4+1 */
        if(four){
            ret[0] = 8;
            ret[1] = four;
            ret[2] = one;
            return ret;
        }
        /* 3+2 */
        if(three && !tok.empty()){
            ret[0] = 7;
            ret[1] = three;
            ret[2] = tok[0];
            return ret;
        }
        /* 同花 */
        if(th){
            ret[0] = 6;
            sort(b.begin(), b.end(), [](int xx, int yy){ return xx > yy; });
            for(int i = 0; i < 5; i++) ret[i+1] = b[i];
            return ret;
        }
        /* 顺子 */
        if(sh){
            ret[0] = 5;
            ret[1] = sh;
            return ret;
        }
        /* 3+1+1 */
        if(three){
            ret[0] = 4;
            ret[1] = three;
            vector<int> c;
            for(int i = 2; i <= 14; i++) if(cnt[i] == 1) c.pb(i);
            sort(c.begin(), c.end(), [](int xx, int yy){ return xx > yy; });
            for(int i = 0; i < (int)c.size(); i++) ret[i+2] = c[i];
            return ret;
        }
         /* 2+2+1 */
        if(tok.size() == 2){
            ret[0] = 3;
            sort(tok.begin(), tok.end(), [](int xx, int yy){ return xx > yy; });
            ret[1] = tok[0];
            ret[2] = tok[1];
            ret[3] = one;
            return ret;
        }
         /* 2+1+1+1 */
        if(tok.size() == 1){
            ret[0] = 2;
            ret[1] = tok[0];
            vector<int> c;
            for(int i = 2; i <= 14; i++) if(cnt[i] == 1) c.pb(i);
            sort(c.begin(), c.end(), [](int xx, int yy){ return xx > yy; });
            for(int i = 0; i < (int)c.size(); i++) ret[i+2] = c[i];
            return ret;
        }
        ret[0] = 1;
        sort(b.begin(), b.end(), [](int xx, int yy){ return xx > yy; });
        for(int i = 0; i < 5; i++) ret[i+1] = b[i];
        return ret;
    };

    array<int,6> val1[52], val2[52];
    for(int i = 0; i < 52; i++){
        if(vis[i]) continue;
        vector<pair<int,char>> a = {s[1],s[2],s[3],s[4],cun[i]};
        vector<pair<int,char>> b = {s[5],s[6],s[7],s[8],cun[i]};
        val1[i] = get1(a);
        val2[i] = get1(b);
    }
    auto get2 = [](array<int,6> a, array<int,6> b) -> int {
        for(int i = 0; i < 6; i++){
            if(a[i] != b[i]) return a[i] > b[i] ? 1LL : -1LL;
        }
        return 0LL;
    };
    int ok = 1;
    for(int x = 0; x < 52; x++){
        if(vis[x]) continue;
        int me = 0;
        int op = 1;
        for(int y = 0; y < 52; y++){
            if(vis[y] || x == y) continue;
            int z = get2(val1[y], val2[x]);
            if(z > 0) me = 1;
            if(z >= 0) op = 0;
        }
        if(op){
            cout << "GeiWoCaPiXie" << endl;
            return;
        }
        if(!me) ok = 0;
    }
    if(ok) cout << "WoYaoYanPai" << endl;
    else cout << "PaiMeiYouWenTi" << endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}

