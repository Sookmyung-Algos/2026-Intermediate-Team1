#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int n = s.size();

    vector<int> pi(n, 0);

    // 1. Prefix Function 계산
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];

        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }

        if (s[i] == s[j]) {
            j++;
        }

        pi[i] = j;
    }

    // 2. Prefix 출현 횟수 계산
    vector<int> cnt(n + 1, 0);

    for (int i = 0; i < n; i++) {
        cnt[pi[i]]++;
    }

    for (int i = n; i >= 1; i--) {
        cnt[pi[i - 1]] += cnt[i];
    }

    for (int i = 0; i <= n; i++) {
        cnt[i]++;
    }

    // 3. 가장 긴 Prefix = Suffix 찾기
    int len = pi[n - 1];

    while (len > 0) {
        if (cnt[len] >= 3) {
            cout << s.substr(0, len);
            return 0;
        }

        len = pi[len - 1];
    }

    cout << "Just a legend";

    return 0;
}
