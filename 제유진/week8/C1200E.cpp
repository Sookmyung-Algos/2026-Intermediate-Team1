#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    string result;

    for (int k = 0; k < n; k++) {
        string word;
        cin >> word;

        // 첫 번째 단어는 그대로 저장
        if (result.empty()) {
            result = word;
            continue;
        }

        // result의 뒤쪽과 word의 앞쪽만 비교
        string suffix = result.substr(
            max(0, (int)result.size() - (int)word.size())
        );

        // KMP를 위한 문자열 생성
        string combined = word + "#" + suffix;

        int m = combined.size();
        vector<int> pi(m, 0);

        // Prefix Function 계산
        for (int i = 1; i < m; i++) {
            int j = pi[i - 1];

            while (j > 0 && combined[i] != combined[j]) {
                j = pi[j - 1];
            }

            if (combined[i] == combined[j]) {
                j++;
            }

            pi[i] = j;
        }

        // 가장 긴 겹치는 길이
        int overlap = pi[m - 1];

        // 겹치는 부분을 제외하고 추가
        result += word.substr(overlap);
    }

    cout << result;

    return 0;
}
