#include <bits/stdc++.h>
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
const int N = 1e6, mod = 1e9 + 7, inf = 1e18 + 5;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<vector<pii> > cunl(n + 1);
    vector<vector<pii> > cunr(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    stack<pair<int, int> > st;
    for (int i = 1; i <= n; i++)
    {
        while (st.size())
        {
            pii o = st.top();
            if (a[i] > o.first)
            {
                st.pop();
            }
            else
            {
                break;
            }
        }
        for (int k=0;k<=1;k++)
        {
            if(st.size()==0)
            {
                break;
            }
            cunl[i].push_back(st.top());
            st.pop();
        }
        for (int j = cunl[i].size() - 1; j >= 0; j--)
        {
            int x = cunl[i][j].first;
            int y = cunl[i][j].second;
            st.push({x, y});
        }
        st.push({a[i], i});
    }

    stack<pair<int, int> > st2;

    for (int i = n; i >= 1; i--)
    {
        while (st2.size())
        {
            pii o = st2.top();
            if (a[i] > o.first)
            {
                st2.pop();
            }
            else
            {
                break;
            }
        }
        for (int k=0;k<=1;k++)
        {
            if(st2.size()==0)
            {
                break;
            }
            cunr[i].push_back(st2.top());
            st2.pop();
        }
        for (int j = cunr[i].size() - 1; j >= 0; j--)
        {
            int x = cunr[i][j].first;
            int y = cunr[i][j].second;
            st2.push({x, y});
        }
        st2.push({a[i], i});
    }

    int ans = 0;
    for(int i = 1; i <= n; i++){
        if(cunl[i].size() != 0){
            int rr=n;
            int l1 = cunl[i][0].second;
            int l2 = l1-1;
            if(cunl[i].size() >= 2){
                l2 = cunl[i][1].second;
            }
            if(cunr[i].size() != 0){
                rr=cunr[i][0].second;
            }
            int res = (rr - i + 1) * (l1 - l2); 
            ans += res;
        } 
        
        if(cunr[i].size() != 0){
            int ll = 1;
            int r1 = cunr[i][0].second;
            int r2 = n+1;
            if(cunr[i].size() >= 2){
                r2 = cunr[i][1].second;
            }
            if(cunl[i].size() != 0){
                ll=cunl[i][0].second;
            }
            int res = (ll - i + 1) * (r2 - r1); 
            ans += res;
        }
        cout << ans << endl;
    }
    cout << ans << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}