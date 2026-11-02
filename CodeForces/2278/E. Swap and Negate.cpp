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
    1 2 3 4 5
    a b c d e


    i j
    2 4 (偶)

    a b -d -c e
    a d -b -c e
    a d c b e (交换对应位置)

    

    i j (奇)
    2 5
    a -c -b d e
    a -c -d b e
    a -c -d -e -b
    a -c e d -b

    a -e c d -b (交换对应位置并取反)


    * 位置i: a[i] * -1^(j-i)

    我们要求的是所有位置之和最大化,此时不要盯着单个数字看它跳到哪里
    而是把数组看成 n 个固定坑位,一半奇数一半偶数
    
    如果填进奇数坑：
    原本就在奇数位的数（i 奇 -> j 奇）：距离是偶数，贡献为 +a[i]
    原本在偶数位的数（i 偶 -> j 奇）：距离是奇数，贡献为 -a[i]

    如果填进偶数坑：
    原本在奇数位的数（i 奇 -> j 偶）：距离是奇数，贡献为 -a[i]
    原本在偶数位的数（i 偶 -> j 偶）：距离是偶数，贡献为 +a[i]

    现规则看起来很对称但表达很繁琐，就该进入下一步——变量代换

*/
void solve(){
    int n; cin >> n;
    vii a(n+1);
    for(int i = 1; i <= n; i++){
        int x; cin >> x;
        if(i&1) a[i] = x;
        else a[i] = -x;
    }
    sort(a.begin() + 1, a.end(), greater<int>());
    int sum = 0;
    for(int i = 1; i <= (n+1)/2; i++){
        sum += a[i];
    }
    for(int i = (n+1)/2 + 1; i <= n; i++){
        sum -= a[i];
    }
    cout << sum << endl;
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