#include <iostream>
#include <vector>

using namespace std;

int N, Q;
vector<int> arr;
vector<int> tree;

// 세그먼트 트리 구성
void build(int node, int start, int end) {
  if (start == end) {
    tree[node] = arr[start];  // 리프 노드
  } else {
    int mid = (start + end) / 2;

    build(2 * node, start, mid);        // 왼쪽 자식
    build(2 * node + 1, mid + 1, end);  // 오른쪽 자식

    tree[node] = tree[2 * node] + tree[2 * node + 1];  // 구간 합
  }
}

// 구간 합 쿼리: [l, r]
int query(int node, int start, int end, int l, int r) {
  if (r < start || end < l) return 0;             // 겹치지 않음
  if (l <= start && end <= r) return tree[node];  // 완전 포함

  int mid = (start + end) / 2;

  return query(2 * node, start, mid, l, r) +
         query(2 * node + 1, mid + 1, end, l, r);
}

// 값 갱신: idx 위치를 val로 변경
void update(int node, int start, int end, int idx, int val) {
  if (start == end) {
    arr[idx] = val;
    tree[node] = val;
  } else {
    int mid = (start + end) / 2;

    if (idx <= mid)
      update(2 * node, start, mid, idx, val);
    else
      update(2 * node + 1, mid + 1, end, idx, val);

    tree[node] = tree[2 * node] + tree[2 * node + 1];
  }
}

int main() {
  cin >> N >> Q;
  arr.resize(N + 1);  // 1-based
  tree.resize(4 * N);

  for (int i = 1; i <= N; ++i) cin >> arr[i];

  build(1, 1, N);  // root = 1, 구간 = [1, N]

  for (int i = 0; i < Q; ++i) {
    int cmd;
    cin >> cmd;

    if (cmd == 1) {
      int l, r;
      cin >> l >> r;
      cout << query(1, 1, N, l, r) << '\n';
    } else if (cmd == 2) {
      int idx, val;

      cin >> idx >> val;

      update(1, 1, N, idx, val);
    }
  }

  return 0;
}
