#include <iostream>
#include <vector>
#include <deque>
#include <tuple>
#include <algorithm>

using namespace std;

const int MAX_COORD = 105;
const int INF = 1e9;

bool grid[MAX_COORD + 5][MAX_COORD + 5];
int dist[MAX_COORD + 5][MAX_COORD + 5][4];

bool is_obs(int x, int y) {
    if (x < 0 || x > MAX_COORD || y < 0 || y > MAX_COORD) return false;
    return grid[y][x];
}

bool can_go(int x, int y, int d) {
    if (d == 0) return !(is_obs(x, y) && is_obs(x, y - 1));
    if (d == 1) return !(is_obs(x, y - 1) && is_obs(x - 1, y - 1));
    if (d == 2) return !(is_obs(x - 1, y) && is_obs(x - 1, y - 1));
    if (d == 3) return !(is_obs(x, y) && is_obs(x - 1, y));
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int sx, sy, tx, ty;
    if (!(cin >> sx >> sy >> tx >> ty)) return 0;

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2, x3, y3, x4, y4;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

        int minX = min({ x1, x2, x3, x4 });
        int maxX = max({ x1, x2, x3, x4 });
        int minY = min({ y1, y2, y3, y4 });
        int maxY = max({ y1, y2, y3, y4 });

        int oppX = (minX == x2) ? maxX : minX;
        int oppY = (minY == y2) ? maxY : minY;

        int empty_minX = min(x4, oppX);
        int empty_maxX = max(x4, oppX);
        int empty_minY = min(y4, oppY);
        int empty_maxY = max(y4, oppY);

        for (int x = minX; x < maxX; ++x) {
            for (int y = minY; y < maxY; ++y) {
                if (x >= empty_minX && x < empty_maxX && y >= empty_minY && y < empty_maxY) {
                    continue; 
                }
                grid[y][x] = true; 
            }
        }
    }

    for (int i = 0; i <= MAX_COORD; ++i) {
        for (int j = 0; j <= MAX_COORD; ++j) {
            for (int d = 0; d < 4; ++d) {
                dist[i][j][d] = INF;
            }
        }
    }

    deque<tuple<int, int, int>> dq;

    for (int i = 0; i < 4; ++i) {
        dist[sx][sy][i] = 0;
        dq.push_back({ sx, sy, i });
    }

    int dx[] = { 1, 0, -1, 0 }; 
    int dy[] = { 0, -1, 0, 1 };

    while (!dq.empty()) {
        auto [x, y, d] = dq.front();
        dq.pop_front();

        int nx = x + dx[d];
        int ny = y + dy[d];
        if (nx >= 0 && nx <= MAX_COORD && ny >= 0 && ny <= MAX_COORD) {
            if (can_go(x, y, d)) {
                if (dist[nx][ny][d] > dist[x][y][d]) {
                    dist[nx][ny][d] = dist[x][y][d];
                    dq.push_front({ nx, ny, d });
                }
            }
        }

        int ld = (d + 3) % 4;
        if (dist[x][y][ld] > dist[x][y][d] + 1) {
            dist[x][y][ld] = dist[x][y][d] + 1;
            dq.push_back({ x, y, ld });
        }

        int rd = (d + 1) % 4;
        if (dist[x][y][rd] > dist[x][y][d] + 1) {
            dist[x][y][rd] = dist[x][y][d] + 1;
            dq.push_back({ x, y, rd });
        }
    }

    int ans = INF;
    for (int i = 0; i < 4; ++i) {
        ans = min(ans, dist[tx][ty][i]);
    }

    cout << ans << "\n";

    return 0;
}