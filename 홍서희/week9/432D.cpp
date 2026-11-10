#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();

    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }

    vector<long long> cnt(n + 1, 0);
    for (int i = 0; i < n; i++) cnt[pi[i]]++;
    for (int L = n; L >= 1; L--) cnt[pi[L - 1]] += cnt[L];
    for (int L = 1; L <= n; L++) cnt[L]++;

    vector<int> borders;
    for (int L = n; L > 0; L = pi[L - 1]) borders.push_back(L);
    reverse(borders.begin(), borders.end());

    cout << borders.size() << "\n";
    for (int L : borders) cout << L << " " << cnt[L] << "\n";
    return 0;
}
