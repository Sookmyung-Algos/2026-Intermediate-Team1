#include <bits/stdc++.h>
using namespace std;

struct Trie {
    Trie* child[10];
    bool finish;
    bool has_child;

    Trie() : finish(false), has_child(false) {
        memset(child, 0, sizeof(child));
    }

    ~Trie() {
        for (int i = 0; i < 10; i++) {
            if (child[i])
                delete child[i];
        }
    }

    // 문자열 삽입
    bool insert(const char* key) {
        if (*key == '\0') {
            finish = true;
            if (has_child) return false;
            return true;
        }

        if (finish) return false;

        int curr = *key - '0';
        if (child[curr] == NULL) {
            child[curr] = new Trie();
            has_child = true;
        }

        return child[curr]->insert(key + 1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
    
        Trie* root = new Trie();
        vector<string>phone(n);
        
        for (int i = 0; i < n; i++) {
            cin >>phone[i];
        }
    
        bool flag = true;
        for (int i = 0; i < n; i++) {
            if (!flag) continue; 
            
            if (!root->insert(phone[i].c_str())) {
                flag = false;
            }
        }
    
        if (flag) cout << "YES\n";
        else cout << "NO\n";
    
        delete root;
    }
    return 0;
    
}
