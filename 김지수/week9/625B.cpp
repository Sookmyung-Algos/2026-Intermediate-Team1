#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, t;
    cin >> s >> t;

    int n = s.size();
    int m = t.size();

    int answer = 0;
    int i = 0;

    while (i + m <= n) {
        if (s.compare(i, m, t) == 0) {
            answer++;
            i += m;
        } else {
            i++;
        }
    }

    cout << answer << '\n';

    return 0;
}
