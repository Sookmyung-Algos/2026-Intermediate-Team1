#include <bits/stdc++.h>
using namespace std;

const int MAX = 100000;

int arr[MAX];
int tree[4*MAX];

int sign(int x){
    if(x > 0) return 1;
    if(x < 0) return -1;
    return 0;
}

void init(int l, int r, int node){
    if(l == r){
        tree[node] = sign(arr[l]);
        return;
    }
    int mid = (l + r) / 2;
    init(l, mid, node*2);
    init(mid+1, r, node*2+1);
    tree[node] = tree[node*2] * tree[node*2+1];
}

void update(int idx, int val, int node, int l, int r){
    if(idx < l || idx > r) return;
    if(l == r){
        tree[node] = sign(val);
        return;
    }
    int mid = (l + r) / 2;
    update(idx, val, node*2, l, mid);
    update(idx, val, node*2+1, mid+1, r);
    tree[node] = tree[node*2] * tree[node*2+1];
}

int query(int ql, int qr, int node, int l, int r){
    if(qr < l || r < ql) return 1;
    if(ql <= l && r <= qr) return tree[node];
    int mid = (l + r) / 2;
    return query(ql, qr, node*2, l, mid) *
           query(ql, qr, node*2+1, mid+1, r);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    while(cin >> n >> k){
        for(int i=0;i<n;i++) cin >> arr[i];
        init(0, n-1, 1);

        for(int i=0;i<k;i++){
            char t;
            int a, b;
            cin >> t >> a >> b;
            if(t == 'C'){
                update(a-1, b, 1, 0, n-1);
            }else{
                int res = query(a-1, b-1, 1, 0, n-1);
                if(res == 0) cout << '0';
                else if(res > 0) cout << '+';
                else cout << '-';
            }
        }
        cout << '\n';
        return 0;
    }
}