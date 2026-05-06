#include <bits/stdc++.h>
using namespace std;

const int MAX = 100000;

int arr[MAX];
int tree[4*MAX];

int isEven(int x){
    return (x % 2 == 0);
}

void init(int l, int r, int node){
    if(l == r){
        tree[node] = isEven(arr[l]);
        return;
    }
    int mid = (l + r) / 2;
    init(l, mid, node*2);
    init(mid+1, r, node*2+1);
    tree[node] = tree[node*2] + tree[node*2+1];
}

void update(int idx, int val, int node, int l, int r){
    if(idx < l || idx > r) return;

    if(l == r){
        tree[node] = isEven(val);
        return;
    }

    int mid = (l + r) / 2;
    update(idx, val, node*2, l, mid);
    update(idx, val, node*2+1, mid+1, r);
    tree[node] = tree[node*2] + tree[node*2+1];
}

int query(int ql, int qr, int node, int l, int r){
    if(qr < l || r < ql) return 0;
    if(ql <= l && r <= qr) return tree[node];

    int mid = (l + r) / 2;
    return query(ql, qr, node*2, l, mid)
         + query(ql, qr, node*2+1, mid+1, r);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    for(int i=0;i<n;i++) cin >> arr[i];

    init(0, n-1, 1);

    int q;
    cin >> q;

    while(q--){
        int t, a, b;
        cin >> t >> a >> b;

        if(t == 1){
            update(a-1, b, 1, 0, n-1);
        }
        else if(t == 2){
            cout << query(a-1, b-1, 1, 0, n-1) << '\n';
        }
        else{
            int evenCnt = query(a-1, b-1, 1, 0, n-1);
            int len = b - a + 1;
            cout << (len - evenCnt) << '\n';
        }
    }
}