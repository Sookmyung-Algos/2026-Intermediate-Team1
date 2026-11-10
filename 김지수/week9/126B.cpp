
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int n = s.size();
    vector<int> pi(n, 0);

    // 1. pi 배열 계산
    for (int i = 1, j = 0; i < n; i++) {
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }

        if (s[i] == s[j]) {
            pi[i] = ++j;
        }
    }

    // 2. 중간에 등장하는 최대 접두사 길이
    int mx = 0;
    for (int i = 0; i < n - 1; i++) {
        mx = max(mx, pi[i]);
    }

    // 3. 접두사이면서 접미사인 후보
    int len = pi[n - 1];

    while (len > 0) {
        if (len <= mx) {
            cout << s.substr(0, len) << '\n';
            return 0;
        }

        len = pi[len - 1];
    }

    cout << "Just a legend\n";
    return 0;
}
