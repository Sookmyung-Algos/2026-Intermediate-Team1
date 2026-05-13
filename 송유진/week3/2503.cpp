#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int M, N;
int grid[105][105];
int comp[105][105];
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

vector<int> adj[10005];
int q[10005];
int dist_arr[10005];
int visited[10005];
int vis_token = 0;

int distA[10005];
int distB[10005];
pair<int, int> order[10005];

int get_farthest(int start, int* dists) {
    vis_token++;
    int head = 0, tail = 0;
    q[tail++] = start;
    visited[start] = vis_token;
    dists[start] = 0;
    int farthest_node = start;

    while (head < tail) {
        int u = q[head++];
        farthest_node = u;
        for (int v : adj[u]) {
            if (visited[v] != vis_token) {
                visited[v] = vis_token;
                dists[v] = dists[u] + 1;
                q[tail++] = v;
            }
        }
    }
    return farthest_node;
}

int get_max_dist(int start_node, int limit) {
    vis_token++;
    int head = 0, tail = 0;
    q[tail++] = start_node;
    visited[start_node] = vis_token;
    dist_arr[start_node] = 0;
    int max_dist = 0;

    while (head < tail) {
        int u = q[head++];
        max_dist = dist_arr[u];
        if (max_dist >= limit) return limit;

        for (int v : adj[u]) {
            if (visited[v] != vis_token) {
                visited[v] = vis_token;
                dist_arr[v] = dist_arr[u] + 1;
                q[tail++] = v;
            }
        }
    }
    return max_dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> M >> N)) return 0;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
            comp[i][j] = -1;
        }
    }

    int comp_cnt = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (comp[i][j] == -1) {
                int head = 0, tail = 0;
                q[tail++] = i * N + j;
                comp[i][j] = comp_cnt;

                while (head < tail) {
                    int curr = q[head++];
                    int cy = curr / N;
                    int cx = curr % N;

                    for (int d = 0; d < 4; d++) {
                        int ny = cy + dy[d];
                        int nx = cx + dx[d];
                        if (ny >= 0 && ny < M && nx >= 0 && nx < N) {
                            if (comp[ny][nx] == -1 && grid[ny][nx] == grid[cy][cx]) {
                                comp[ny][nx] = comp_cnt;
                                q[tail++] = ny * N + nx;
                            }
                        }
                    }
                }
                comp_cnt++;
            }
        }
    }

    if (comp_cnt <= 1) {
        cout << 0 << "\n";
        return 0;
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            int u = comp[i][j];
            for (int d = 0; d < 4; d++) {
                int ny = i + dy[d];
                int nx = j + dx[d];
                if (ny >= 0 && ny < M && nx >= 0 && nx < N) {
                    int v = comp[ny][nx];
                    if (u != v) {
                        adj[u].push_back(v);
                    }
                }
            }
        }
    }

    for (int i = 0; i < comp_cnt; i++) {
        sort(adj[i].begin(), adj[i].end());
        adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
    }

    int A = get_farthest(0, distA);
    int B = get_farthest(A, distA);
    get_farthest(B, distB);

    for (int i = 0; i < comp_cnt; i++) {
        order[i] = { max(distA[i], distB[i]), i };
    }
    sort(order, order + comp_cnt);

    int min_max_dist = 1e9;
    for (int i = 0; i < comp_cnt; i++) {
        int lower_bound = order[i].first;
        int start_node = order[i].second;

        if (lower_bound >= min_max_dist) {
            break;
        }

        int d = get_max_dist(start_node, min_max_dist);
        if (d < min_max_dist) {
            min_max_dist = d;
        }
    }

    cout << min_max_dist << "\n";

    return 0;
}