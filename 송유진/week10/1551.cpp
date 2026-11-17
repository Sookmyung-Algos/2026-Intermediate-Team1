#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25000 * 20 + 1;
int ch[MAXN][26], cntNode = 1;
bool isEnd[MAXN];
string longest, ops;

void dfs(int u, int depth, bool onPath) {
    if (isEnd[u]) ops += 'P';
    int last = onPath && depth < (int)longest.size() ? longest[depth] - 'a' : -1;
    for (int c = 0; c < 26; c++) {
        if (!ch[u][c] || c == last) continue;
        ops += char('a' + c);
        dfs(ch[u][c], depth + 1, false);
        ops += '-';
    }
    if (last != -1) {              
        ops += char('a' + last);
        dfs(ch[u][last], depth + 1, true);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        if (s.size() > longest.size()) longest = s;
        int u = 0;
        for (char c : s) {
            if (!ch[u][c - 'a']) ch[u][c - 'a'] = cntNode++;
            u = ch[u][c - 'a'];
        }
        isEnd[u] = true;
    }
    dfs(0, 0, true);
    string out = to_string(ops.size()) + '\n';
    for (char c : ops) { out += c; out += '\n'; }
    cout << out;
}
