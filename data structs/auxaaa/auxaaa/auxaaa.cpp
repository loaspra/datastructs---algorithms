#include <bits/stdc++.h>
#include <unordered_map>
#define F first
#define S second
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define RFOR(i, a, b) for(int i = a; i >= b; i--)
#define all(v) ((v).begin()), ((v).end())
#define endl '\n'

using namespace std;
using ll = long long;
using ull = unsigned long long;
using Graph = vector<vector<int>>;
using vi = vector<int>;
using vl = vector<ll>;
using vll = vector<ll, ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);


    int t;
    cin >> t;
    while (t--) {
        int n, m;
        unordered_map<int, int> l1;
        unordered_map<int, int> l2;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            int x; cin >> x;
            //cout << "l1_" <<l1[x] << endl;
            l1[x]++;
           // cout << "l1_" << l1[x] << endl;
        }
        cout << "l1_" << l1[0] << endl;
        for (int i = 0; i < m; i++) {
            int x; cin >> x;
            l2[x]++;
        }
        int ans = 0;
        for (auto a : l1) 
        {
            cout << "a_" << a.first << endl;
            ans += abs(l2[a.first] - a.second);
        }
        cout << ans * 2 << endl;
    }
}