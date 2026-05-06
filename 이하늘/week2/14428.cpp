#include <iostream>
#include <vector>

using namespace std;

// first는 값, second는 인덱스
using pii = pair<int, int>;

const int MAX_VAL = 2000000000;

pii merge(pii left, pii right) {
    // 값이 같을 경우
    if (left.first == right.first) {
        return (left.second < right.second) ? left : right;
    }
    //더 작은 애.
    return (left.first < right.first) ? left : right;
}

pii init(vector<int>& arr, vector<pii>& tree, int node, int start, int end) {
    if (start == end) {
        return tree[node] = {arr[start], start + 1}; //1-based
    }
    int mid = (start + end) / 2;
    return tree[node] = merge(init(arr, tree, node * 2, start, mid), 
                              init(arr, tree, node * 2 + 1, mid + 1, end));
}

pii query(vector<pii>& tree, int node, int start, int end, int left, int right) {
    if (left > end || right < start) {
        return {MAX_VAL, MAX_VAL};
    }
    if (left <= start && end <= right) return tree[node];
    
    int mid = (start + end) / 2;
    return merge(query(tree, node * 2, start, mid, left, right), 
                 query(tree, node * 2 + 1, mid + 1, end, left, right));
}

void update(vector<pii>& tree, int node, int start, int end, int index, int val) {
    if (index < start || index > end) return;
    if (start == end) {
        tree[node] = {val, start + 1};
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
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 1) update(tree, 1, 0, n - 1, b - 1, c);
        else if (a == 2) cout << query(tree, 1, 0, n - 1, b - 1, c - 1).second << "\n";
    return 0;
}