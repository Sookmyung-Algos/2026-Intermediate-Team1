#include <iostream>
#include <vector>

using namespace std;

vector<int> arr;
// first: 값, second: 인덱스
vector<pair<int, int>> tree;

void build(int node, int start, int end){
    if (start == end){
        tree[node].first = arr[start];
        tree[node].second = start;
    } else {
        int mid = (start + end) / 2;

        build(2* node, start, mid);
        build(2* node + 1, mid + 1, end);

        if (tree[2* node].first < tree[2* node +1].first){
            tree[node].first = tree[2* node].first;
            tree[node].second = tree[2* node].second;
        } else {
            tree[node].first = tree[2* node + 1].first;
            tree[node].second = tree[2* node + 1].second;
        }
    }
}

// l,r : 찾고 싶은 구간
pair<int, int> query(int node, int start, int end, int l, int r){
    if (start > r || end < l) return {INT_MAX, INT_MAX};
    if (start >= l && end <= r) return tree[node];

    int mid = (start + end) / 2;
    pair<int, int> left_pair = query(2* node, start, mid, l, r);
    pair<int, int> right_pair = query(2* node + 1, mid + 1, end, l, r);

    if (left_pair.first < right_pair.first){
        return left_pair;
    } else if ((left_pair.first > right_pair.first)){
        return right_pair;
    } else {  // 두 값이 같은 경우 더 작은 인덱스 반환
        if (left_pair.second < right_pair.second) return left_pair;
        else return right_pair;
    }
}

void update(int node, int start, int end, int idx, int val){
    if (start == end){
        tree[node].first = val;
        arr[idx] = val;
    } else {
        int mid = (start + end) / 2;
        if (idx <= mid){
            update(2*node, start, mid, idx, val);
        } else {
            update(2*node + 1, mid + 1, end, idx, val);
        }
        
        if (tree[2* node].first < tree[2* node +1].first){
            tree[node] = tree[2* node];
        } else if (tree[2* node].first > tree[2* node +1].first){
            tree[node] = tree[2* node + 1];
        }  else { // 두 값이 모두 같은 경우
            if (tree[2* node].second < tree[2* node+1].second){
                tree[node] = tree[2* node];
            } else {
                tree[node] = tree[2* node + 1];
            }
        }
    }
}

// B14428 - 수열과 쿼리 16
int main(){
    int N, M, x, p, q;
    cin >> N;
    arr.resize(N);
    tree.resize(8*N);
    for (int i = 0; i < N; i++){
        cin >> arr[i];
    }
    build(1, 0, N-1);
    cin >> M;
    for (int i = 0; i < M; i++){
        cin >> x >> p >> q;
        if (x == 1){    // update
            update(1, 0, N-1, p-1, q);
        } else if (x == 2){ // 크기가 가장 작은 값의 인덱스 출력
            cout << query(1, 0, N-1, p-1, q-1).second + 1 << '\n';
        }
    }
}
