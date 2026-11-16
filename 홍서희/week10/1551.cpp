#include <bits/stdc++.h>
using namespace std;

const int MAXNODE = 25000 * 20 + 1;

int child[MAXNODE][26];
bool finish[MAXNODE];
int maxRest[MAXNODE];
int cnt;

string ops;

void insert(const string& s) {
    int cur = 0;
    int len = s.size();
    for (int i = 0; i < len; i++) {
        maxRest[cur] = max(maxRest[cur], len - i);
        int c = s[i] - 'a';
        if (!child[cur][c]) child[cur][c] = ++cnt;
        cur = child[cur][c];
    }
    finish[cur] = true;
}

void dfs(int node, bool onPath) {
    if (finish[node]) ops += 'P';
    int heavy = -1;
    for (int c = 0; c < 26; c++) {
        int nx = child[node][c];
        if (nx && (heavy == -1 || maxRest[nx] > maxRest[child[node][heavy]]))
            heavy = c;
    }

    for (int c = 0; c < 26; c++) {
        if (!child[node][c] || c == heavy) continue;
        ops += char('a' + c);
        dfs(child[node][c], false);
        ops += '-';
    }

    if (heavy != -1) {
        ops += char('a' + heavy);
        dfs(child[node][heavy], onPath);
        if (!onPath) ops += '-';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        insert(s);
    }

    dfs(0, true);

    string out = to_string(ops.size()) + '\n';
    out.reserve(ops.size() * 2 + 16);
    for (char ch : ops) {
        out += ch;
        out += '\n';
    }
    cout << out;
    return 0;
}
