
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

    // 2. 각 pi 값의 등장 횟수 계산
    vector<int> cnt(n + 1, 0);

    for (int i = 0; i < n; i++) {
        cnt[pi[i]]++;
    }

    // 3. 긴 접두사의 등장 횟수를
    //    짧은 접두사에 누적
    for (int len = n; len > 0; len--) {
        cnt[pi[len - 1]] += cnt[len];
    }

    // 4. 각 접두사 자기 자신의 등장 횟수 추가
    for (int len = 1; len <= n; len++) {
        cnt[len]++;
    }

    // 5. 접두사이면서 접미사인 길이 찾기
    vector<pair<int, int>> answer;

    int len = n;

    while (len > 0) {
        answer.push_back({len, cnt[len]});
        len = pi[len - 1];
    }

    // 6. 길이 오름차순 출력
    reverse(answer.begin(), answer.end());

    cout << answer.size() << '\n';

    for (auto [length, count] : answer) {
        cout << length << " " << count << '\n';
    }

    return 0;
}
