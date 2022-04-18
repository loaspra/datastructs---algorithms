#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;

string ini;
stack<char> aux;
vector<stack<char>> v;


int containers(int i) {
    for (long unsigned int j = 0; j < v.size(); ++j) {
        if (ini[i] >= v[j].top()) {
            v[j].push(ini[i]);
            return 0;
        }
    }
    v.push_back(aux);
    v[v.size() - 1].push(ini[i]);
    return 1;
}


int main() {

    int n, t = 0;
    while (cin >> ini && ini != "FIN") {
        t++;
        n = ini.size();
        v.clear();

        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans += containers(i);
        }
        cout << "Caso " << t << ": " << ans << endl;
        printf("Caso %d: %d\n", t, ans);
    }
}