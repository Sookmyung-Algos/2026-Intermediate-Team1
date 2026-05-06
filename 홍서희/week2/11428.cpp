#include <iostream>
#include<vector>
using namespace std;;
typedef long long ll;
 
int n, m;
ll arr[100001];
vector<pair<ll,ll>> tree;

pair<ll,ll> minimum(pair<ll,ll>a,pair<ll,ll>b){
    if(a.first>b.first) return b;
    else if(a.first==b.first){
        if(a.second>b.second) return b;
        else return a;
    }
    else return a;
    
}
 
pair<ll,ll> make_tree(int node, int start, int end)
{
    if (start == end) return tree[node]={arr[start],start};
 
    int mid = (start + end) / 2;
    
    return tree[node] = minimum(make_tree(node * 2, start, mid), make_tree(node * 2 + 1, mid + 1, end));
}
 
pair<ll,ll> query(int node, int start, int end, int left, int right)
{
    if (left > end || start > right) return {10000000000,1000000000};
 
    if (left <= start && end <= right) return tree[node];
 
    int mid = (start + end) / 2;
    return minimum(query(node * 2, start, mid, left, right),query(node * 2 + 1, mid + 1, end, left, right));
}
 
void update(int node, int start, int end, int idx, ll value)
{
    if (idx < start || end < idx) return;
 
    if (start == end)
    {
        tree[node] = {value,idx};
        return;
    }
 
    int mid = (start + end) / 2;
    update(node * 2, start, mid, idx, value);
    update(node * 2 + 1, mid + 1, end, idx, value);
    tree[node] = minimum(tree[node * 2] , tree[node * 2 + 1]);
}
 
 
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    cin >> n;
 
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
 
    tree.resize(n * 4);
 
    make_tree(1, 1, n);
    cin >> m;
 
    for (int i = 0; i < m; i++)
    {
        ll a, b, c;
        cin >> a >> b >> c;
        if (a == 1)
            update(1, 1, n, b, c);
        else if(a==2){
            pair<ll,ll> ans=query(1, 1, n, b, c);
            cout<<ans.second<<"\n";
            
        }
    }
 
    return 0;
}