#include <cstdio>
#include <deque>
#define MAX 100
using namespace std;

int n, m, ans;
int map[MAX][MAX];
int visited[MAX][MAX];
int dx[] = { 1,0,0,-1 };
int dy[] = { 0,1,-1,0 };

struct Info{
	int x, y, sum;
};
 
void bfs() {
	deque<Info> deq;
	deq.push_back({ 0,0,0 });
	visited[0][0] = 1;
	while (!deq.empty())
	{
		auto cur = deq.front(); deq.pop_front();
		int x = cur.x;
		int y = cur.y;
		int sum = cur.sum;
		if (x == n - 1 and y == m - 1) {
			printf("%d ", sum);
			return;
		}

		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx >= n or ny >= m or nx < 0 or ny < 0) continue;
			if (visited[nx][ny]) continue;
			visited[nx][ny] = 1;
			if (map[nx][ny]) {
				deq.push_back({ nx,ny,sum + 1 });
			}
			else deq.push_front({ nx,ny,sum });
		}
	}
	return;
}
int main() {

	 scanf("%d %d", &m, &n);
	 for (int i = 0; i < n; ++i){
		for (int j = 0; j < m; ++j) {
			scanf("%1d", &map[i][j]); 
		} 
     }
	bfs();
	return 0;
}