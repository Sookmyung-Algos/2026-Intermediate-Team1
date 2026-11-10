#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    string res;
    cin >> res;

    for (int k = 1; k < n; k++) {
        string w;
        cin >> w;

        int len = min(res.size(), w.size());
        string t = w + '#' + res.substr(res.size() - len);

        int m = t.size();
        vector<int> pi(m, 0);
        for (int i = 1; i < m; i++) {
            int j = pi[i - 1];
            while (j > 0 && t[i] != t[j]) j = pi[j - 1];
            if (t[i] == t[j]) j++;
            pi[i] = j;
        }

        res += w.substr(pi[m - 1]);
    }

    cout << res << "\n";
    return 0;
}
