#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        unordered_map<string, int> cnt;
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            char c; string s; cin >> c >> s;
            if (c == 'I') {
                for (int len = 1; len <= (int)s.size(); len++) cnt[s.substr(0, len)]++;
            } else {
                auto it = cnt.find(s);
                ans.push_back(it == cnt.end() ? 0 : it->second);
            }
        }
        for (size_t i = 0; i < ans.size(); i++) cout << ans[i] << (i + 1 < ans.size() ? ' ' : '\n');
        if (ans.empty()) cout << '\n';
    }
}
