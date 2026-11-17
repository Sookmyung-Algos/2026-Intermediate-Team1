
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Node {
    int next[26];
    int cnt;

    Node() {
        for (int i = 0; i < 26; i++) {
            next[i] = -1;
        }
        cnt = 0;
    }
};

vector<Node> trie;

// 문자열 삽입
void insertString(string s) {
    int cur = 0;

    for (char c : s) {
        int idx = c - 'A';

        if (trie[cur].next[idx] == -1) {
            trie[cur].next[idx] = trie.size();
            trie.push_back(Node());
        }

        cur = trie[cur].next[idx];
        trie[cur].cnt++;
    }
}

// 접두사를 가지는 문자열 개수 조회
int findString(string s) {
    int cur = 0;

    for (char c : s) {
        int idx = c - 'A';

        if (trie[cur].next[idx] == -1) {
            return 0;
        }

        cur = trie[cur].next[idx];
    }

    return trie[cur].cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        trie.clear();
        trie.push_back(Node());

        for (int i = 0; i < N; i++) {
            char cmd;
            string s;

            cin >> cmd >> s;

            if (cmd == 'I') {
                insertString(s);
            }
            else if (cmd == 'O') {
                cout << findString(s) << " ";
            }
        }

        cout << "\n";
    }

    return 0;
}
