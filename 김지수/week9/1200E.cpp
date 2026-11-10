#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    string result;
    cin >> result;

    for (int k = 1; k < n; k++) {
        string word;
        cin >> word;

        // 1. 비교할 접미사 길이
        int len = min(result.size(), word.size());

        // 2. word + '#' + result의 접미사
        string temp = word + "#" +
            result.substr(result.size() - len);

        // 3. pi 배열 계산
        int m = temp.size();
        vector<int> pi(m, 0);

        for (int i = 1, j = 0; i < m; i++) {
            while (j > 0 && temp[i] != temp[j]) {
                j = pi[j - 1];
            }

            if (temp[i] == temp[j]) {
                pi[i] = ++j;
            }
        }

        // 4. 가장 길게 겹치는 부분
        int overlap = pi[m - 1];

        // 5. 겹치지 않는 부분만 추가
        result += word.substr(overlap);
    }

    cout << result << '\n';

    return 0;
}
