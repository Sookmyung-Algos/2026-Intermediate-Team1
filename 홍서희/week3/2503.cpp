#include <bits/stdc++.h>
using namespace std;

int M, N;
int color[105][105];
int id[105][105];

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

vector<int> g[10005];
int distArr[10005];
int qArr[10005];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> M >> N;

    for (int r = 0; r < M; r++)
    {
        for (int c = 0; c < N; c++)
        {
            cin >> color[r][c];
            id[r][c] = -1;
        }
    }

    int C = 0;

    // 1. 같은 색 영역 압축
    for (int r = 0; r < M; r++)
    {
        for (int c = 0; c < N; c++)
        {
            if (id[r][c] != -1)
                continue;

            queue<pair<int, int>> q;
            q.push({r, c});
            id[r][c] = C;

            while (!q.empty())
            {
                auto [x, y] = q.front();
                q.pop();

                for (int d = 0; d < 4; d++)
                {
                    int nx = x + dr[d];
                    int ny = y + dc[d];

                    if (nx < 0 || nx >= M || ny < 0 || ny >= N)
                        continue;
                    if (id[nx][ny] != -1)
                        continue;
                    if (color[nx][ny] != color[x][y])
                        continue;

                    id[nx][ny] = C;
                    q.push({nx, ny});
                }
            }

            C++;
        }
    }

    // 2. 컴포넌트 그래프 생성
    for (int r = 0; r < M; r++)
    {
        for (int c = 0; c < N; c++)
        {
            int u = id[r][c];

            if (r + 1 < M)
            {
                int v = id[r + 1][c];
                if (u != v)
                {
                    g[u].push_back(v);
                    g[v].push_back(u);
                }
            }

            if (c + 1 < N)
            {
                int v = id[r][c + 1];
                if (u != v)
                {
                    g[u].push_back(v);
                    g[v].push_back(u);
                }
            }
        }
    }

    for (int i = 0; i < C; i++)
    {
        sort(g[i].begin(), g[i].end());
        g[i].erase(unique(g[i].begin(), g[i].end()), g[i].end());
    }

    // 3. 중앙에서 가까운 컴포넌트 순서 만들기
    vector<int> order;
    bool visitedCell[105][105] = {};

    queue<pair<int, int>> cq;
    cq.push({M / 2, N / 2});
    visitedCell[M / 2][N / 2] = true;

    bool usedComp[10005] = {};
    int checkedCompCnt = 0;

    while (!cq.empty())
    {
        auto [r, c] = cq.front();
        cq.pop();

        int cid = id[r][c];

        if (!usedComp[cid])
        {
            usedComp[cid] = true;
            order.push_back(cid);
            checkedCompCnt++;

            if (checkedCompCnt > C / 2)
                break;
        }

        for (int d = 0; d < 4; d++)
        {
            int nr = r + dr[d];
            int nc = c + dc[d];

            if (nr < 0 || nr >= M || nc < 0 || nc >= N)
                continue;
            if (visitedCell[nr][nc])
                continue;

            visitedCell[nr][nc] = true;
            cq.push({nr, nc});
        }
    }

    int ans = C;

    for (int s : order)
    {
        fill(distArr, distArr + C, -1);

        int head = 0, tail = 0;
        qArr[tail++] = s;
        distArr[s] = 0;

        int mx = 0;
        bool cut = false;

        while (head < tail)
        {
            int cur = qArr[head++];

            if (distArr[cur] >= ans)
            {
                cut = true;
                break;
            }

            mx = max(mx, distArr[cur]);

            for (int nxt : g[cur])
            {
                if (distArr[nxt] != -1)
                    continue;

                distArr[nxt] = distArr[cur] + 1;
                qArr[tail++] = nxt;
            }
        }

        if (!cut)
        {
            ans = min(ans, mx);
        }
    }

    cout << ans << '\n';
    return 0;
}