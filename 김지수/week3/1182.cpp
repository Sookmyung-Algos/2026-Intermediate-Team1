#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

const int CELL = 1000;
const int MAX_POS = 30000;
const int MAX_CELL = MAX_POS / CELL + 1;
const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, F;
    cin >> H >> F;

    vector<Point> hold(F);
    vector<int> bucket[MAX_CELL][MAX_CELL];

    for (int i = 0; i < F; i++) {
        cin >> hold[i].x >> hold[i].y;

        int cx = hold[i].x / CELL;
        int cy = hold[i].y / CELL;

        bucket[cx][cy].push_back(i);
    }

    int START = F;
    int TOP = F + 1;

    vector<int> dist(F + 2, INF);
    vector<bool> visited(F + 2, false);

    deque<int> dq;

    dist[START] = 0;
    dq.push_back(START);

    while (!dq.empty()) {
        int cur = dq.front();
        dq.pop_front();

        if (visited[cur]) continue;
        visited[cur] = true;

        if (cur == TOP) {
            cout << dist[cur] << '\n';
            return 0;
        }

        if (cur == START) {
            for (int i = 0; i < F; i++) {
                if (hold[i].y <= 1000) {
                    if (dist[i] > dist[cur] + 1) {
                        dist[i] = dist[cur] + 1;
                        dq.push_back(i);
                    }
                }
            }
            continue;
        }

        if (hold[cur].y >= H - 1000) {
            if (dist[TOP] > dist[cur]) {
                dist[TOP] = dist[cur];
                dq.push_front(TOP);
            }
        }

        int cx = hold[cur].x / CELL;
        int cy = hold[cur].y / CELL;

        for (int nx = max(0, cx - 1); nx <= min(MAX_CELL - 1, cx + 1); nx++) {
            for (int ny = max(0, cy - 1); ny <= min(MAX_CELL - 1, cy + 1); ny++) {
                for (int next : bucket[nx][ny]) {
                    if (visited[next]) continue;
                    if (next == cur) continue;

                    int dx = abs(hold[cur].x - hold[next].x);
                    int dy = abs(hold[cur].y - hold[next].y);

                    if (dx > 1000 || dy > 1000) continue;

                    if (1LL * dx * dx + 1LL * dy * dy <= 1000000) {
                        if (dist[next] > dist[cur] + 1) {
                            dist[next] = dist[cur] + 1;
                            dq.push_back(next);
                        }
                    }
                }
            }
        }
    }

    cout << -1 << '\n';

    return 0;
}
