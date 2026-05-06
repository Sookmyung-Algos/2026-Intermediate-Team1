#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX = 1000000;

ll tree[4*MAX];
ll arr[MAX];

int n, m;

void update(int idx, ll diff, int node, int l, int r){
    if(idx < l || idx > r) return;

    tree[node] += diff;

    if(l == r) return;

    int mid = (l + r) / 2;
    update(idx, diff, node*2, l, mid);
    update(idx, diff, node*2+1, mid+1, r);
}

ll query(int ql, int qr, int node, int l, int r){
    if(qr < l || r < ql) return 0;
    if(ql <= l && r <= qr) return tree[node];

    int mid = (l + r) / 2;
    return query(ql, qr, node*2, l, mid)
         + query(ql, qr, node*2+1, mid+1, r);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;

    while(m--){
        int t;
        ll a, b;
        cin >> t >> a >> b;

        if(t == 0){
            if(a > b) swap(a, b);
            cout << query(a-1, b-1, 1, 0, n-1) << '\n';
        }
        else{
            ll diff = b - arr[a-1];
            arr[a-1] = b;
            update(a-1, diff, 1, 0, n-1);
        }
    }
}