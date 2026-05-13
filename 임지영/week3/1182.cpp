
// 정올 1182 벽타기

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int X[10001], Y[10001];
int dist[10001]; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int H, F;
    if (!(cin >> H >> F)) return 0;

    for (int i = 0; i < F; i++) {
        cin >> X[i] >> Y[i];
        dist[i] = -1; // -1로 초기화 (미방문 상태)
    }

    queue<int> q;

    // 시작점 설정: 지면에서 1000mm 이하인 지지대들
    for (int i = 0; i < F; i++) {
        if (Y[i] <= 1000) {
            q.push(i);
            dist[i] = 1; // 첫 번째 지지대 밟음
        }
    }

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        // 현재 지지대에서 꼭대기(H)까지 도달 가능한지
        if (Y[cur] >= H - 1000) {
            cout << dist[cur] << endl;
            return 0;
        }

        // 다음 지지대 탐색
        for (int next = 0; next < F; next++) {
            // 이미 방문했거나 자기 자신인 경우 스킵
            if (dist[next] != -1) continue;

            // 거리 계산
            long long dx = (long long)X[cur] - X[next];
            long long dy = (long long)Y[cur] - Y[next];
            long long d_squared = dx * dx + dy * dy;

            // 두 지지대 사이의 거리가 1000mm(1,000,000 mm^2) 이하인지
            if (d_squared <= 1000000) {
                dist[next] = dist[cur] + 1;
                q.push(next);
            }
        }
    }

    return 0;
}