#include <iostream>
#include <vector>

using namespace std;

vector<int> arr;
vector<int> tree;

void build(int node, int start, int end){
    if (start == end){ // 리프노드
        tree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        build(2* node, start, mid);
        build(2* node + 1, mid + 1, end);

        tree[node] = tree[2*node] + tree[2* node +1];
    }
}

// l,r : 구하고 싶은 질의 구간
int query(int node, int start, int end, int l, int r){
    if (r < start || l > end) return 0;
    if (l <= start && r >= end) return tree[node];

    int mid = (start + end) / 2;
    int left_sum = query(2*node, start, mid, l,r);
    int right_sum = query(2*node+1, mid +1, end, l,r);

    return left_sum + right_sum;
}

void update(int node, int start, int end, int idx, int val){
    if (start == end){
        arr[idx] = val;
        tree[node] = val;
    } else {
        int mid = (start + end) / 2;

        if (idx <= mid){
            update(2* node, start, mid, idx, val);
        } else {
            update(2* node+1, mid +1, end, idx, val);
        }
        tree[node] = tree[2*node]+ tree[2*node+1];
    }
}

// B2268 - 수들의 합 7
int main(){
    int N, M, x, p, q;
    cin >> N >> M;
    arr.resize(N, 0);
    tree.resize(4*N);

    build(1, 0, N-1);

    for (int i = 0; i < M; i++){
        cin >> x >> p >> q;
        if (x == 0){
            cout << query(1, 0, N-1, p, q);
        } else if(x == 1){
            update(1, 0, N-1, p, q);
        }
    }

}
