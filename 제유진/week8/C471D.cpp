#include <bits/stdc++.h>
using namespace std;

vector<int> getPi(vector<int>& p) {
    int m = p.size();
    vector<int> pi(m, 0);

    for (int i = 1; i < m; i++) {
        int j = pi[i - 1];

        while (j > 0 && p[i] != p[j]) {
            j = pi[j - 1];
        }

        if (p[i] == p[j]) {
            j++;
        }

        pi[i] = j;
    }

    return pi;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, w;
    cin >> n >> w;

    vector<int> a(n), b(w);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < w; i++) {
        cin >> b[i];
    }

    // 길이가 1이면 모든 위치에서 일치
    if (w == 1) {
        cout << n;
        return 0;
    }

    // 1. 차분 배열 생성
    vector<int> diffA, diffB;

    for (int i = 0; i < n - 1; i++) {
        diffA.push_back(a[i + 1] - a[i]);
    }

    for (int i = 0; i < w - 1; i++) {
        diffB.push_back(b[i + 1] - b[i]);
    }

    // 2. 패턴의 Prefix Function 계산
    vector<int> pi = getPi(diffB);

    // 3. KMP 검색
    int ans = 0;
    int j = 0;

    for (int i = 0; i < diffA.size(); i++) {

        while (j > 0 && diffA[i] != diffB[j]) {
            j = pi[j - 1];
        }

        if (diffA[i] == diffB[j]) {
            j++;
        }

        if (j == diffB.size()) {
            ans++;
            j = pi[j - 1];
        }
    }

    cout << ans;

    return 0;
}
