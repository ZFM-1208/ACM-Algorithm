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

void solve(){
    int n; cin >> n;
    string s1,s7; cin >> s1 >> s7;
    int cn1 = 0, cn2 = 0;
    int p1=-1,p7=-1;
    for(int i = 0; i < n; i++){
        if(s1[i] == '#') {
            cn1++;
            if(i>=1&&s1[i-1]=='.')
            {
                p1=i;
            }
            if(i<n-1&&s1[i+1]=='.')
            {
                p1=i;
            }
        }
        if(s7[i] == '#'){
            cn2++;
            if(i>=1&&s7[i-1]=='.')
            {
                p7=i;
            }
             if(i<n-1&&s7[i+1]=='.')
            {
                p7=i;
            }
        }
    }
    if((cn1 == n && cn2 != n) || (cn2 == n && cn1 != n)){
        cout << "No" << endl;
        return;
    }
    if(cn1 == n && cn2 == n){
        cout << "Yes\n";
        cout << s1<<"\n";
        for(int j = 1; j <= 5; j++){
            for(int i = 1; i <= n; i++){
                cout << "#";
            }
            cout << endl;
        }
        cout << s7 << endl;
        return;
    }
    cout << "Yes\n";
    cout << s1<<"\n";

    for(int i = 0; i < n; i++){
        if(s1[i] == '#') {
            cout << ".";
        }
        else
        {
            cout <<"#";
        }
    }
    cout <<"\n";
    for(int i = 0; i < n; i++){
        if(i==p1) {
            cout << "#";
        }
        else
        {
            cout <<".";
        }
    }
    cout << "\n";
    if(p1!=p7&&abs(p1-p7)>1)
    {
        for(int i = 0; i < n; i++){
            if(i<max(p1,p7)&&i>min(p1,p7)) {
                cout << "#";
            }
            else
            {
                cout <<".";
            }
        }
        cout <<"\n";
    }
    else if(abs(p1-p7)==1)
    {
        for(int i = 0; i < n; i++){
            if(i==p1) {
                cout << "#";
            }
            else
            {
                cout <<".";
            }
        }
        cout <<"\n";
    }
    else
    {
        int l=p1-1,r=p1+1;
        if(l<0)
        {
            for(int i = 0; i < n; i++){
                if(i==r) {
                    cout << "#";
                }
                else
                {
                    cout <<".";
                }
            }
            cout <<"\n";
        }
        else
        {
            for(int i = 0; i < n; i++){
                if(i==l) {
                    cout << "#";
                }
                else
                {
                    cout <<".";
                }
            }
            cout <<"\n";
        }
    }
    for(int i = 0; i < n; i++){
        if(i==p7) {
            cout << "#";
        }
        else
        {
            cout <<".";
        }
    }
    cout << "\n";
    
    for(int i = 0; i < n; i++){
        if(s7[i] == '#') {
            cout << ".";
        }
        else
        {
            cout <<"#";
        }
    }
    cout <<"\n";
    cout << s7<<"\n";
    string s2;
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