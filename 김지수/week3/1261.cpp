#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

const int INF = 1e9;

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCase;
    cin >> testCase;

    while (testCase--) {
        int K;
        cin >> K;

        int M, N;
        cin >> M >> N;

        vector<vector<char>> maze(M, vector<char>(N));
        vector<vector<int>> dist(M, vector<int>(N, INF));

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

        deque<pair<int, int>> dq;

        dist[sx][sy] = 0;
        dq.push_front({sx, sy});

        while (!dq.empty()) {
            int x = dq.front().first;
            int y = dq.front().second;
            dq.pop_front();

            for (int dir = 0; dir < 4; dir++) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];

                if (nx < 0 || nx >= M || ny < 0 || ny >= N) {
                    continue;
                }

                int cost = 0;

                if (maze[nx][ny] == '*') {
                    cost = 1;
                }

                int nextDist = dist[x][y] + cost;

                if (nextDist > K) {
                    continue;
                }

                if (dist[nx][ny] > nextDist) {
                    dist[nx][ny] = nextDist;

                    if (cost == 0) {
                        dq.push_front({nx, ny});
                    } else {
                        dq.push_back({nx, ny});
                    }
                }
            }
        }

        if (dist[tx][ty] <= K) {
            cout << "y\n";
        } else {
            cout << "n\n";
        }
    }

    return 0;
}
