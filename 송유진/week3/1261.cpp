#include <iostream>
#include <vector>
#include <string>
#include <deque>

using namespace std;

int M, N;
string maze[105];
int dist[105][105];
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> M >> N)) return 0;

    for (int i = 0; i < N; i++) {
        cin >> maze[i];
        for (int j = 0; j < M; j++) {
            dist[i][j] = 1e9;
        }
    }

    deque<pair<int, int>> dq;
    dq.push_back({ 0, 0 });
    dist[0][0] = 0;

    while (!dq.empty()) {
        int y = dq.front().first;
        int x = dq.front().second;
        dq.pop_front();

        if (y == N - 1 && x == M - 1) {
            cout << dist[y][x] << "\n";
            return 0;
        }

        for (int d = 0; d < 4; d++) {
            int ny = y + dy[d];
            int nx = x + dx[d];

            if (ny >= 0 && ny < N && nx >= 0 && nx < M) {
                int cost = maze[ny][nx] - '0';
                if (dist[y][x] + cost < dist[ny][nx]) {
                    dist[ny][nx] = dist[y][x] + cost;
                    if (cost == 0) {
                        dq.push_front({ ny, nx });
                    }
                    else {
                        dq.push_back({ ny, nx });
                    }
                }
            }
        }
    }

    return 0;
}