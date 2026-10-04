#include<bits/stdc++.h>
using namespace std;
#define rep(i, l, r) for (int i = l; i <= r; i++)
#define pii pair<int, int>
#define int long long
#define pb push_back
#define fi first
#define se second
#define endl '\n'
double pi = acos(-1);
const int N = 1e6, mod = 1e9+7, inf = 1e18 + 5;
int fpow(int a,int b){
    int res = 1;
    while(b){
        if(b&1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res % mod;
}
const int base = 13331;
void solve(){
	int n,q,m,k; cin >> n >> q >> m >> k;
	vector<string> a(n+1);
	vector<vector<int>> hs(n+1,vector<int>(m+2,0));
	vector<int> p(m+2);
	p[0] = 1;
	for(int i = 1; i <= m; i++){
		p[i] = p[i-1] * base % mod;
	}	
	for(int qq = 1; qq <= n; qq++){
		cin >> a[qq];
		a[qq] = " " + a[qq];
		for(int i = 1; i <= m; i++){
			hs[qq][i] = (hs[qq][i-1] * base + a[qq][i]) % mod;
		}
	}
    auto get_hash = [&] (int i, int l, int r) -> int {
        int res = (hs[i][r] - hs[i][l-1] * p[r-l+1] % mod + mod) % mod;
        return res;
    };
	while(q--){
		string s; cin >> s;
		s = " " + s;
		vector<int> hx(m+2);
		for(int i = 1; i <= m; i++){
			hx[i] = (hx[i-1] * base + s[i]) % mod;
		}
		
		auto get_hash1 = [&] (int l, int r) -> int {
			int res = (hx[r] - hx[l-1] * p[r-l+1] % mod + mod) % mod;
			return res;
		};
		int ans = 0;
		for(int qq = 1; qq <= n; qq++){
			int cnt = 0;
			int lst = 1;
			while(lst <= m)
			{
				int l = 1, r = m - lst+1;
				int lcp = 0;
				while(l <= r)
				{
					int mid = (l + r) / 2;
					int hxn = get_hash(qq,lst,lst+mid-1);
					int hxs = get_hash1(lst,lst+mid-1);
					if(hxn == hxs){
						lcp = mid;
						l = mid + 1;
					}else{
						r = mid - 1;
					}
				}
				cnt++;
				if(lst+lcp-1 == m) cnt--;
				// cout << "L: " << lst << " R:" << p << endl;
				lst = lst + lcp - 1 + 2;
				if(cnt > k){
					ans++;
					break;
				}
			}
			// cout << endl;
		}
		cout << n - ans << endl;
	}
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T = 1;
    //cin >> T;
    while(T--)
        solve();
    return 0;
}