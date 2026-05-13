
// 정올 2503 그리드 게임 

#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

const int fx[] = { 0,1,0,-1 }, fy[] = { 1,0,-1,0 };
vector<int> adj[10001];
int s[100][100], c[100][100], m, n, cnt, pcnt, r = 1e9;
pair<int, int> p[40000];

void ff(int x, int y, int ss, int cc) {
    if (x < 0 || y < 0 || x >= m || y >= n || s[x][y] ^ ss || c[x][y]) return;
    c[x][y] = cc;
    for (int i = 0; i < 4; i++) ff(x + fx[i], y + fy[i], ss, cc);
}

int main() {
    scanf("%d%d", &m, &n);
    
    for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) scanf("%d", &s[i][j]);
    for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) if (!c[i][j]) ff(i, j, s[i][j], ++cnt);
    for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) for (int k = 0; k < 4; k++) {
        int tx = i + fx[k], ty = j + fy[k];
        if (tx >= 0 && ty >= 0 && tx < m && ty < n && s[i][j] ^ s[tx][ty]) p[pcnt++] = { c[i][j],c[tx][ty] };
    }

    sort(p, p + pcnt);
    
    pcnt = unique(p, p + pcnt) - p;
    
    while (pcnt--) adj[p[pcnt].first].push_back(p[pcnt].second);
    
    for (int i = 1; i <= cnt; i++) {
        int q[10000], ck[10001] = { 0, }, h = 0, t = 1;
        ck[i] = 1; q[0] = i;
        while (h^t && ck[q[h]]<r) {
            for (auto it : adj[q[h]]) if (!ck[it]) {
                ck[it] = ck[q[h]] + 1;
                q[t++] = it;
            }
            h++;
        }
        r = ck[q[t - 1]];
    }
    printf("%d", r - 1);
    return 0;
}