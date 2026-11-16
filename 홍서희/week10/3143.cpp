#include <bits/stdc++.h>
using namespace std;

const int MAXNODE = 1000 * 9 + 1;

int child[MAXNODE][26];
int passCnt[MAXNODE];
int cnt;

int newNode() {
    ++cnt;
    memset(child[cnt], 0, sizeof(child[cnt]));
    passCnt[cnt] = 0;
    return cnt;
}

void insert(const string& s) {
    int cur = 0;
    for (char ch : s) {
        int c = ch - 'A';
        if (!child[cur][c]) {
            int nx = newNode();
            child[cur][c] = nx;
        }
        cur = child[cur][c];
        passCnt[cur]++;
    }
}

int query(const string& s) {
    int cur = 0;
    for (char ch : s) {
        int c = ch - 'A';
        if (!child[cur][c]) return 0;
        cur = child[cur][c];
    }
    return passCnt[cur];
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

        vector<int> ans;
        for (int i = 0; i < n; i++) {
            char c;
            string s;
            cin >> c >> s;
            if (c == 'I') insert(s);
            else ans.push_back(query(s));
        }

        for (size_t i = 0; i < ans.size(); i++) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}
