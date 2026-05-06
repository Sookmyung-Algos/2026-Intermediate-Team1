#include <iostream>
#include <vector>

using namespace std;

// 나머지 연산용
const long long MOD = 1000000007;

long long init(vector<long long>& arr, vector<long long>& tree, int node, int start, int end) {
    if (start == end) {
        return tree[node] = arr[start];
    }
    int mid = (start + end) / 2;
    return tree[node] = (init(arr, tree, node * 2, start, mid) * 
                         init(arr, tree, node * 2 + 1, mid + 1, end)) % MOD;
}

long long query(vector<long long>& tree, int node, int start, int end, int left, int right) {
    if (left > end || right < start) {
        return 1;
    }
    if (left <= start && end <= right) {
        return tree[node];
    }
    int mid = (start + end) / 2;
    return (query(tree, node * 2, start, mid, left, right) * 
            query(tree, node * 2 + 1, mid + 1, end, left, right)) % MOD;
}

void update(vector<long long>& tree, int node, int start, int end, int index, long long val) {
    if (index < start || index > end) {
        return;
    }
    if (start == end) {
        tree[node] = val;
        return;
    }
    int mid = (start + end) / 2;
    update(tree, node * 2, start, mid, index, val);
    update(tree, node * 2 + 1, mid + 1, end, index, val);
    
    tree[node] = (tree[node * 2] * tree[node * 2 + 1]) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    vector<long long> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    vector<long long> tree(n * 4);
    init(arr, tree, 1, 0, n - 1);

    for (int i = 0; i < m + k; i++) {
        long long a, b, c;
        cin >> a >> b >> c;
        if (a == 1) update(tree, 1, 0, n - 1, b - 1, c);
        else if (a == 2) cout << query(tree, 1, 0, n - 1, b - 1, c - 1) << "\n";
    }
    return 0;
}