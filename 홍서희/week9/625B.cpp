#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, b;
    cin >> a >> b;

    int cnt = 0;
    size_t pos = a.find(b);
    while (pos != string::npos) {
        cnt++;
        pos = a.find(b, pos + b.size());
    }

    cout << cnt << "\n";
    return 0;
}
