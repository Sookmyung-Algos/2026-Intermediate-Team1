#include <bits/stdc++.h>

using namespace std;
int T, K, M, N, startx, starty, endx, endy;
char arr[501][501];
int dist[501][501];
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
struct Elements
{
    int x, y, energy;
};

bool zero_onebfs(int stx, int sty, int K, int edx, int edy)
{
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
            dist[i][j] = 1e9;
    }
    deque<Elements> dq;
    dq.push_back(Elements{stx, sty, 0});
    dist[stx][sty] = 0;
    while (!dq.empty())
    {
        int cur_x = dq.front().x;
        int cur_y = dq.front().y;
        int cur_energy = dq.front().energy;
        dq.pop_front();

        if (cur_x == edx && cur_y == edy && cur_energy <= K)
            return true;

        for (int i = 0; i < 4; i++)
        {
            int next_x = cur_x + dx[i];
            int next_y = cur_y + dy[i];
            if (next_x < 0 || next_x >= M || next_y < 0 || next_y >= N)
                continue;
            int weight = (arr[next_x][next_y] == '*' ? 1 : 0);
            int next_energy = cur_energy + weight;
            if (next_energy <= K && next_energy < dist[next_x][next_y])
            {
                dist[next_x][next_y] = next_energy;
                if (weight == 0)
                {
                    dq.push_front({next_x, next_y, next_energy});
                }
                else
                {
                    dq.push_back({next_x, next_y, next_energy});
                    ;
                }
            }
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> T;
    while (T--)
    {
        cin >> K;
        cin >> M >> N;
        memset(arr, '0', sizeof(arr));
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cin >> arr[i][j];
                if (arr[i][j] == 'S')
                {
                    startx = i;
                    starty = j;
                }
                if (arr[i][j] == 'T')
                {
                    endx = i;
                    endy = j;
                }
            }
        }
        if (zero_onebfs(startx, starty, K, endx, endy))
            cout << 'y' << '\n';
        else
            cout << 'n' << '\n';
    }

    return 0;
}