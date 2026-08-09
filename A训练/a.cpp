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
const int N = 1e6, inf = 1e18 + 5;
std::vector<int> ext_kmp(string s, int n){
    vector<int> z(n,0);
    for(int i = 1, x = 0, y = 0; i < n; i++){
        if(i <= y) z[i] = min(y-i, z[i-x]);
        while(i + z[i] < n && s[i+z[i]] == s[z[i]]) z[i]++;
        if(y <= i + z[i]) x = i, y = i + z[i];
    }
    z[0] = n;
    return z;
}
void solve(){
    string s; cin >> s;
    int sz = s.size();
    vector<int> z = ext_kmp(s, sz);
    for(int i = 1; i < sz; i++) {
        if(z[i] == sz - i) {
            cout << 0 << endl;
            return;
        }
    }
    vector<char> chars;
    vector<bool> vis(26);
    for(char c : s){
        if(!vis[c-'a']){
            vis[c-'a'] = 1;
            chars.pb(c);
        }
    }
    auto it = find(chars.begin(), chars.end(), s[0]);
    swap(*chars.begin(), *it);
    int m = chars.size();
    vector<int> id(26,-1);
    for(int i = 0; i < m; i++) id[chars[i]-'a'] = i;
    vector<vector<int>> adj(m);
    vector<int> du(m);
    map<pii, int> has_edge;
    for(int i = 1; i < sz; i++) {
        int u = id[s[z[i]]-'a'], v = id[s[i+z[i]]-'a'];
        if(!has_edge[{u, v}]) {
            has_edge[{u, v}] = 1;
            adj[u].pb(v);
            du[v]++;
        }
    }

    queue<int> q;
    for(int i = 0; i < m; i++){
        if(du[i] == 0) q.push(i);
    }

    int cnt = 0;
    while(!q.empty()){
        int u = q.front(); q.pop();
        cnt++;
        for(int v : adj[u]){
            if(--du[v] == 0) q.push(v);
        }
    }
    if(cnt < m){
        cout << 0 << endl; 
        return;
    }
    // 纠正 3：用状压 DP 计算拓扑序方案数（替换原来的 DFS，防止 TLE）
    int N_nodes = m - 1; // 扣除首字母 s[0]
    if(N_nodes == 0) {
        cout << 0 << endl;
        return;
    }

    // 构建子图中各节点的前驱节点掩码
    vector<int> in_mask(N_nodes, 0);
    for(int u = 1; u < m; u++) {
        for(int v : adj[u]) {
            if(v != 0) {
                in_mask[v - 1] |= (1 << (u - 1));
            }
        }
    }

    // uint32_t 自然溢出即相当于对 2^32 取模，完美解决模 2^32 无法求逆元的问题
    int max_mask = 1 << N_nodes;
    vector<uint32_t> dp(max_mask, 0);
    dp[0] = 1;

    for(int mask = 0; mask < max_mask; mask++) {
        uint32_t cur = dp[mask];
        if(cur == 0) continue;

        for(int v = 0; v < N_nodes; v++) {
            if(!(mask & (1 << v)) && ((in_mask[v] & mask) == in_mask[v])) {
                dp[mask | (1 << v)] += cur;
            }
        }
    }

    uint32_t ans = dp[max_mask - 1];
    for(int i = m + 1; i <= 26; i++) {
        ans *= i; 
    }
    cout << (long long)ans << endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    return 0;
}
