#include <iostream>
#include <vector>

using namespace std;

// first는 짝수 개수, second는 홀수 개수
using pii = pair<int, int>;

pii merge(pii left, pii right) {
    return {left.first + right.first, left.second + right.second};
}

pii init(vector<int>& arr, vector<pii>& tree, int node, int start, int end) {
    if (start == end) {
        // 짝수 {1, 0}, 홀수 {0, 1}
        if (arr[start] % 2 == 0) return tree[node] = {1, 0};
        else return tree[node] = {0, 1};
    }
    int mid = (start + end) / 2;
    return tree[node] = merge(init(arr, tree, node * 2, start, mid), 
                              init(arr, tree, node * 2 + 1, mid + 1, end));
}

pii query(vector<pii>& tree, int node, int start, int end, int left, int right) {
    if (left > end || right < start) return {0, 0}; // 범위 밖이면 {0,0}
    if (left <= start && end <= right) return tree[node];
    
    int mid = (start + end) / 2;
    return merge(query(tree, node * 2, start, mid, left, right), 
                 query(tree, node * 2 + 1, mid + 1, end, left, right));
}

void update(vector<pii>& tree, int node, int start, int end, int index, int val) {
    if (index < start || index > end) return;
    if (start == end) {
        if (val % 2 == 0) tree[node] = {1, 0};
        else tree[node] = {0, 1};
        return;
    }
    int mid = (start + end) / 2;
    update(tree, node * 2, start, mid, index, val);
    update(tree, node * 2 + 1, mid + 1, end, index, val);
    
    tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    vector<pii> tree(n * 4);
    init(arr, tree, 1, 0, n - 1);

    int m; cin >> m;
    for (int i = 0; i < m; i++) {
        int cmd, b, c;
        cin >> cmd >> b >> c;
        if (cmd == 1) update(tree, 1, 0, n - 1, b - 1, c);
        else if (cmd == 2) cout << query(tree, 1, 0, n - 1, b - 1, c - 1).first << "\n"; // 짝수 
        else if (cmd == 3) cout << query(tree, 1, 0, n - 1, b - 1, c - 1).second << "\n"; // 홀수
    }
    return 0;
}