#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, t;
    cin >> s >> t;

    int n = s.size();
    int m = t.size();

    int ans = 0;

    int i = 0;

    while (i + m <= n) {

        // 현재 위치에서 t와 일치하는지 확인
        if (s.substr(i, m) == t) {
            ans++;

            // 겹치지 않도록 t의 길이만큼 이동
            i += m;
        }
        else {
            i++;
        }
    }

    cout << ans;

    return 0;
}
