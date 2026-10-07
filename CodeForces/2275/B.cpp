#include<bits/stdc++.h>
using namespace std;
#define rep(i, l, r) for(int i = l; i <= r; i++)
#define vii vector<int>
#define pii pair<int, int>
#define int long long
#define pb push_back
#define fi first
#define se second
#define endl '\n'
double pi = acos(-1);
const int N = 1e6, mod = 1e9+7, inf = 1e18 + 5;

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    vii vis(n+1);
    stack<int> st; 
	s = " " + s;
    for(int i = 1; i <= n; i++) {
        if(s[i] == '1') {
            st.push(i);
        } else if(s[i] == '2') {
            if(!st.empty()) {
				vis[st.top()] = 1;
                st.pop();               
            } else {
                vis[i] = 1;
            }
        } else if(s[i] == '3') {
            vis[i] = 1;
        }
    }
    vector<int> ans;
    for(int i = 1; i <= n; i++) {
        if(!vis[i])  ans.pb(i);
    }
    cout << ans.size() << "\n";
	for(int x: ans) cout << x << " ";
	cout << endl;
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