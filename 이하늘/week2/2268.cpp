#include <iostream>
#include <vector>

using namespace std;

long long query(vector<long long>& tree, int node, int start, int end, int left, int right) {
    if (left > end || right < start) {
        return 0;
    }
    if (left <= start && end <= right) {
        return tree[node];
    }
    int mid = (start + end) / 2;
    return query(tree, node * 2, start, mid, left, right) + 
           query(tree, node * 2 + 1, mid + 1, end, left, right);
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
    
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;

    cin >> n >> m;

    vector<long long> tree(n * 4, 0); 
    
    for (int i = 0; i < m; i++) {
        long long a, b, c;
        cin >> a >> b >> c;
        
        if (a == 0) {
            if (b > c) {
                swap(b, c);
            }
            cout << query(tree, 1, 0, n - 1, b - 1, c - 1) << "\n";
            
        } else if (a == 1) {
            update(tree, 1, 0, n - 1, b - 1, c);
        }
    }

    return 0;
}