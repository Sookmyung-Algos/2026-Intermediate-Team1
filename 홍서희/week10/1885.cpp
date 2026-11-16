#include <bits/stdc++.h>
using namespace std;

const int MAXNODE = 10000 * 100 + 1;

int child[MAXNODE][10];
bool finish[MAXNODE];
int cnt;

int newNode() {
    ++cnt;
    memset(child[cnt], 0, sizeof(child[cnt]));
    finish[cnt] = false;
    return cnt;
}

bool insert(const string& s) {
    int cur = 0;
    bool created = false;
    for (char ch : s) {
        if (finish[cur]) return false;
        int c = ch - '0';
        if (!child[cur][c]) {
            int nx = newNode();
            child[cur][c] = nx;
            created = true;
        }
        cur = child[cur][c];
    }
    if (!created) return false;
    finish[cur] = true;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        cnt = 0;
        memset(child[0], 0, sizeof(child[0]));
        finish[0] = false;

        bool flag = true;
        string s;
        for (int i = 0; i < n; i++) {
            cin >> s;
            if (flag && !insert(s)) flag = false;
        }
        cout << (flag ? "YES\n" : "NO\n");
    }
    return 0;
}
