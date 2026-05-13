
// 정올 1134 미로

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstring>

#define MAX 501
#define INF 100001

using namespace std;

int maze[MAX][MAX];
int dist[MAX][MAX] = {INF, }; // 소모한 최소 에너지 저장 배열
deque<pair<int, int>> weight;

// 상하 좌우 이동
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

pair<int, int> start;
pair<int, int> to;


int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T; cin >> T;
    
    while(T-->0){
        int K; cin >> K; // 에너지
        int M, N; cin >> M; cin >> N; // 미로 크기
        
        // 미로 및 가중치 초기화
        for(int i = 0; i < M; i++) {
            for(int j = 0; j < N; j++) {
                dist[i][j] = INF; 
                maze[i][j] = 0;
            }
        }
        weight.clear();

        // 미로 정의 & 시작, 도착 위치 저장
        for(int i=0; i<M; i++){
            for(int j=0; j<N; j++){
                char wall; cin >> wall;
                if(wall == '.')
                    maze[i][j] = 0;
                else if (wall == '*')
                    maze[i][j] = 1;
                else if (wall == 'S')
                    start = {i, j};
                else
                    to = {i, j};
            }
        }

        int start_x = start.first;
        int start_y = start.second;

        int to_x = to.first;
        int to_y = to.second;

        // 시작 지점 방문
        weight.push_back({start_x, start_y});
        dist[start_x][start_y] = 0;
        
        // 0-1 bfs
        while(!weight.empty()){
            pair<int, int> cur = weight.front();
            weight.pop_front();

            int x = cur.first; int y = cur.second;

            if(x == to_x && y == to_y && dist[x][y] <= K){
                cout << "y\n";
                break;
            }

            else if(x == to_x && y == to_y && dist[x][y] > K){
                cout << "n\n";
                break;
            }

            // 이동 시작
            for(int i=0; i<4; i++){
                int nx = x + dx[i];
                int ny = y + dy[i];

                // 미로 범위를 벗어나는지 확인
                if (nx < 0 || nx >= M || ny < 0 || ny >= N) continue;

				int cost = maze[nx][ny]; // 빈공간이면 0, 벽이면 1
            
            	// 새로 계산한 비용이 기존 기록보다 작을 때만 갱신
            	if (dist[nx][ny] > dist[x][y] + cost) {
            		
                	dist[nx][ny] = dist[x][y] + cost;

                	// 가중치 0 -> front, 1 -> back
                	if (cost== 0) weight.push_front({nx, ny});
                
                	else if (cost == 1) weight.push_back({nx, ny});
                	
            	}
            }
            
        }
    }
}
