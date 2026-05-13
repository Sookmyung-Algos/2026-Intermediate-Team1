#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    while (T--) {
        int K;
        cin >> K;

        int M, N;
        cin >> M >> N;

        vector<vector<char>> maze(M, vector<char>(N));

        int sx = 0, sy = 0;
        int tx = 0, ty = 0;

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                cin >> maze[i][j];

                if (maze[i][j] == 'S') {
                    sx = i;
                    sy = j;
                } else if (maze[i][j] == 'T') {
                    tx = i;
                    ty = j;
                }
            }
        }

        const int INF = 1e9;
        vector<vector<int>> dist(M, vector<int>(N, INF));
        deque<pair<int, int>> dq;

        dist[sx][sy] = 0;
        dq.push_front({sx, sy});

        bool possible = false;

        while (!dq.empty()) {
            int x = dq.front().first;
            int y = dq.front().second;
            dq.pop_front();

            if (x == tx && y == ty) {
                possible = true;
                break;
            }

            for (int dir = 0; dir < 4; dir++) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];

                if (nx < 0 || nx >= M || ny < 0 || ny >= N) continue;

                int cost = 0;

                if (maze[nx][ny] == '*') {
                    cost = 1;
                }

                int nd = dist[x][y] + cost;

                if (nd > K) continue;

                if (dist[nx][ny] > nd) {
                    dist[nx][ny] = nd;

                    if (cost == 0) {
                        dq.push_front({nx, ny});
                    } else {
                        dq.push_back({nx, ny});
                    }
                }
            }
        }

        if (possible) {
            cout << "y\n";
        } else {
            cout << "n\n";
        }
    }

    return 0;
}
