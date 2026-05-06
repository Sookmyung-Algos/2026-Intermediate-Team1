#include <iostream>
#include <vector>

using namespace std;

vector<int> arr;
vector<int> tree;

// node가 담당하는 구간: start ~ end
void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = (arr[start] % 2 == 0) ? 1 : 0;
        return;
    }

    int mid = (start + end) / 2;

    build(node * 2, start, mid);
    build(node * 2 + 1, mid + 1, end);

    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

// index 위치 값을 value로 변경
void update(int node, int start, int end, int index, int value) {
    if (index < start || index > end) return;

    if (start == end) {
        arr[index] = value;
        tree[node] = (value % 2 == 0) ? 1 : 0;
        return;
    }

    int mid = (start + end) / 2;

    update(node * 2, start, mid, index, value);
    update(node * 2 + 1, mid + 1, end, index, value);

    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

// l ~ r 구간의 짝수 개수
int query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return 0;

    if (l <= start && end <= r) {
        return tree[node];
    }

    int mid = (start + end) / 2;

    int left = query(node * 2, start, mid, l, r);
    int right = query(node * 2 + 1, mid + 1, end, l, r);

    return left + right;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N;

    arr.resize(N + 1);
    tree.resize(4 * N);

    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
    }

    build(1, 1, N);

    cin >> M;

    for (int i = 0; i < M; i++) {
        int x, p, q;
        cin >> x >> p >> q;

        if (x == 1) {
            // p번째 수를 q로 변경
            update(1, 1, N, p, q);
        } 
        else if (x == 2) {
            // p ~ q 중 짝수 개수
            cout << query(1, 1, N, p, q) << '\n';
        } 
        else if (x == 3) {
            // p ~ q 중 홀수 개수
            int evenCount = query(1, 1, N, p, q);
            int length = q - p + 1;
            cout << length - evenCount << '\n';
        }
    }

    return 0;
}
