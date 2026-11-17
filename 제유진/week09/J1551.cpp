
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Node {
    int child[26];
    bool isEnd;

    Node() {
        for (int i = 0; i < 26; i++) {
            child[i] = -1;
        }
        isEnd = false;
    }
};

vector<Node> trie;
vector<int> lastChild;
string answer;

void dfs(int cur) {
    // 현재 노드가 단어의 끝이면 출력
    if (trie[cur].isEnd) {
        answer += 'P';
        answer += '\n';
    }

    // 마지막 경로의 자식은 가장 나중에 방문
    for (int i = 0; i < 26; i++) {
        int next = trie[cur].child[i];

        if (next == -1 || next == lastChild[cur])
            continue;

        // 활자 추가
        answer += char('a' + i);
        answer += '\n';

        dfs(next);

        // 활자 제거
        answer += '-';
        answer += '\n';
    }

    // 마지막 경로의 자식 방문
    int next = lastChild[cur];

    if (next != -1) {
        int ch = -1;

        for (int i = 0; i < 26; i++) {
            if (trie[cur].child[i] == next) {
                ch = i;
                break;
            }
        }

        answer += char('a' + ch);
        answer += '\n';

        dfs(next);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    trie.emplace_back();

    int edgeCount = 0;
    int maxDepth = -1;
    int lastNode = 0;

    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;

        int cur = 0;

        for (char c : s) {
            int idx = c - 'a';

            if (trie[cur].child[idx] == -1) {
                trie[cur].child[idx] = trie.size();
                trie.emplace_back();
                edgeCount++;
            }

            cur = trie[cur].child[idx];
        }

        trie[cur].isEnd = true;

        // 가장 깊은 단어 선택
        if ((int)s.size() > maxDepth) {
            maxDepth = s.size();
            lastNode = cur;
        }
    }

    // 마지막 단어까지의 경로 표시
    lastChild.assign(trie.size(), -1);

    int cur = lastNode;

    while (cur != 0) {
        int parent = -1;

        for (int i = 0; i < (int)trie.size(); i++) {
            for (int j = 0; j < 26; j++) {
                if (trie[i].child[j] == cur) {
                    parent = i;
                    break;
                }
            }

            if (parent != -1)
                break;
        }

        lastChild[parent] = cur;
        cur = parent;
    }

    dfs(0);

    // 마지막 단어 경로를 제외한 제거 횟수는
    // 전체 간선 수 - 마지막 단어 길이
    int M = 2 * edgeCount - maxDepth + N;

    cout << M << '\n';
    cout << answer;

    return 0;
}
