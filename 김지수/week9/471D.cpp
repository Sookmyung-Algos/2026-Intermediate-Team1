
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, w;
    cin >> n >> w;

    vector<long long> a(n), b(w);

    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < w; i++) cin >> b[i];

    if (w == 1) {
        cout << n << '\n';
        return 0;
    }

    if (w > n) {
        cout << 0 << '\n';
        return 0;
    }

    // 1. 차분 배열 생성
    vector<long long> da(n - 1), db(w - 1);

    for (int i = 0; i < n - 1; i++) {
        da[i] = a[i + 1] - a[i];
    }

    for (int i = 0; i < w - 1; i++) {
        db[i] = b[i + 1] - b[i];
    }

    // 2. 패턴 db의 pi 배열 계산
    int m = db.size();
    vector<int> pi(m, 0);

    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && db[i] != db[j]) {
            j = pi[j - 1];
        }

        if (db[i] == db[j]) {
            pi[i] = ++j;
        }
    }

    // 3. KMP로 일치하는 구간 탐색
    int answer = 0;

    for (int i = 0, j = 0; i < (int)da.size(); i++) {
        while (j > 0 && da[i] != db[j]) {
            j = pi[j - 1];
        }

        if (da[i] == db[j]) {
            j++;
        }

        if (j == m) {
            answer++;
            j = pi[j - 1];
        }
    }

    cout << answer << '\n';
    return 0;
}
