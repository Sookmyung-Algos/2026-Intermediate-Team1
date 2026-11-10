#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, w;
    cin >> n >> w;
    vector<long long> a(n), b(w);
    for (auto &x : a) cin >> x;
    for (auto &x : b) cin >> x;

    if (w == 1) {
        cout << n << "\n";
        return 0;
    }

    vector<long long> da(n - 1), db(w - 1);
    for (int i = 0; i + 1 < n; i++) da[i] = a[i + 1] - a[i];
    for (int i = 0; i + 1 < w; i++) db[i] = b[i + 1] - b[i];

    int m = w - 1;
    vector<int> pi(m, 0);
    for (int i = 1; i < m; i++) {
        int j = pi[i - 1];
        while (j > 0 && db[i] != db[j]) j = pi[j - 1];
        if (db[i] == db[j]) j++;
        pi[i] = j;
    }

    long long cnt = 0;
    int j = 0;
    for (int i = 0; i < (int)da.size(); i++) {
        while (j > 0 && da[i] != db[j]) j = pi[j - 1];
        if (da[i] == db[j]) j++;
        if (j == m) {
            cnt++;
            j = pi[j - 1];
        }
    }

    cout << cnt << "\n";
    return 0;
}
