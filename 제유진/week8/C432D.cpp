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

    // 2. Prefix 등장 횟수 계산
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

    // 3. 모든 Prefix = Suffix 찾기
    vector<int> ans;

    int len = n;

    while (len > 0) {
        ans.push_back(len);
        len = pi[len - 1];
    }

    // 4. 길이가 작은 순서대로 출력
    reverse(ans.begin(), ans.end());

    cout << ans.size() << '\n';

    for (int len : ans) {
        cout << len << " " << cnt[len] << '\n';
    }

    return 0;
}
