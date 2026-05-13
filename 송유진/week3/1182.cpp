#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Point {
    long long x, y;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long H;
    int F;
    if (!(cin >> H >> F)) return 0;

    vector<Point> holds(F);
    for (int i = 0; i < F; ++i) {
        cin >> holds[i].x >> holds[i].y;
    }

    vector<int> dist(F, -1);
    queue<int> q;

    for (int i = 0; i < F; ++i) {
        if (holds[i].y <= 1000) {
            dist[i] = 1;
            q.push(i);
        }
    }

    int ans = -1;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        if (holds[curr].y >= H - 1000) {
            ans = dist[curr];
            break;
        }

        for (int i = 0; i < F; ++i) {
            if (dist[i] == -1) {
                long long dx = holds[curr].x - holds[i].x;
                long long dy = holds[curr].y - holds[i].y;
                if (dx * dx + dy * dy <= 1000000LL) {
                    dist[i] = dist[curr] + 1;
                    q.push(i);
                }
            }
        }
    }

    cout << ans << "\n";

    return 0;
}