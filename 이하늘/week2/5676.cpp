#include <iostream>
#include <vector>

using namespace std;

// 부호판단
int sign(int val) {
    if (val > 0) return 1;
    if (val < 0) return -1;
    return 0;
}

int init(vector<int>& arr, vector<int>& tree, int node, int start, int end) {
    if (start == end) return tree[node] = arr[start];
    int mid = (start + end) / 2;
    return tree[node] = init(arr, tree, node * 2, start, mid) * 
                        init(arr, tree, node * 2 + 1, mid + 1, end);
}

int query(vector<int>& tree, int node, int start, int end, int left, int right) {
    if (left > end || right < start)
        return 1;
    if (left <= start && end <= right)
        return tree[node];
    
    int mid = (start + end) / 2;
    return query(tree, node * 2, start, mid, left, right) * 
           query(tree, node * 2 + 1, mid + 1, end, left, right);
}

void update(vector<int>& tree, int node, int start, int end, int index, int val) {
    if (index < start || index > end) return;
    if (start == end) {
        tree[node] = val;
        return;
    }
    int mid = (start + end) / 2;
    update(tree, node * 2, start, mid, index, val);
    update(tree, node * 2 + 1, mid + 1, end, index, val);
    tree[node] = tree[node * 2] * tree[node * 2 + 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    while (cin >> n >> k) {
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            int temp;
            cin >> temp;
            arr[i] = sign(temp);
        }

        vector<int> tree(n * 4);
        init(arr, tree, 1, 0, n - 1);

        for (int i = 0; i < k; i++) {
            char cmd; int b, c;
            cin >> cmd >> b >> c;
            
            if (cmd == 'C') { 
                update(tree, 1, 0, n - 1, b - 1, sign(c));
            } else if (cmd == 'P') { 
                int res = query(tree, 1, 0, n - 1, b - 1, c - 1);
                if (res > 0) cout << "+";
                else if (res < 0) cout << "-";
                else cout << "0";
            }
        }
        cout << "\n";
    }
    return 0;
}