#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<string> v(n);
        for (auto& s : v) cin >> s;
        sort(v.begin(), v.end());
        bool ok = true;
        for (int i = 0; i + 1 < n && ok; i++)
            if (v[i + 1].compare(0, v[i].size(), v[i]) == 0) ok = false;
        cout << (ok ? "YES" : "NO") << '\n';
    }
}
