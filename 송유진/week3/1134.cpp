#include <iostream>
#include <vector>
#include <deque>
#include <string>

using namespace std;

const int INF = 1e9;
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

string solve() {
    int k, m, n;
    cin >> k >> m >> n;

    vector<vector<char>> grid(m, vector<char>(n));
    vector<vector<int>> dist(m, vector<int>(n, INF));

    int sy = -1, sx = -1, ty = -1, tx = -1;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 'S') {
                sy = i; sx = j;
            }
            else if (grid[i][j] == 'T') {
                ty = i; tx = j;
            }
        }
    }

    deque<pair<int, int>> dq;
    dq.push_back({ sy, sx });
    dist[sy][sx] = 0;

    while (!dq.empty()) {
        int y = dq.front().first;
        int x = dq.front().second;
        dq.pop_front();

        if (y == ty && x == tx) break;

        for (int d = 0; d < 4; ++d) {
            int ny = y + dy[d];
            int nx = x + dx[d];

            if (ny >= 0 && ny < m && nx >= 0 && nx < n) {
                int cost = (grid[ny][nx] == '*') ? 1 : 0;

                if (dist[y][x] + cost < dist[ny][nx]) {
                    dist[ny][nx] = dist[y][x] + cost;
                    if (cost == 0) dq.push_front({ ny, nx });
                    else dq.push_back({ ny, nx });
                }
            }
        }
    }

    if (dist[ty][tx] <= k) return "y";
    else return "n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        vector<string> results; 

        while (t--) {
            results.push_back(solve());
        }

        for (const string& res : results) {
            cout << res << "\n";
        }
    }

    return 0;
}