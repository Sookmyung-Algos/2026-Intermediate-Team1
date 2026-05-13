
// 백준 1261 알고스팟

#include <iostream>
#include <deque>
#include <string>
#define MAX 101
#define INF 987654321
using namespace std;

int maze[MAX][MAX]; // 벽 여부 저장
int dist[MAX][MAX]; // 위치로 이동하기까지 부순 벽의 개수
deque<pair<int, int>> dq; // 0-1 bfs 용

// x, y 이동
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int M, N; cin >> M >> N;

    // 미로 정의
    for(int i=0; i<M; i++){
        
        string wall; cin >> wall;

        for(int j=0; j<N; j++){
            maze[i][j] = wall[j] - '0';
        }
    }

    // dist 배열 초기화
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            dist[i][j] = INF;
        }
    }

    int x = 0; int y = 0; // 시작점
    dq.push_back({x, y});
    dist[x][y] = 0;
    
    // 0-1 bfs
    while(!dq.empty()){
        int cx = dq.front().first;
        int cy = dq.front().second;

        dq.pop_front();

        if (cx == N-1 && cy == M-1){
            cout << dist[cx][cy];
            break;
        }

        for(int i=0; i<4; i++){
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            
            // 벽을 넘는 경우
            if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue; // 범위 벗어남
            
            // 벽인 경우
            if (maze[nx][ny] == 1){
                if (dist[nx][ny] > dist[cx][cy] + 1){ // 더 적은 벽을 부순 경우
                    dist[nx][ny] = dist[cx][cy] + 1;
                    dq.push_back({nx, ny});
                }
            }
            else{ // 빈 공간인 경우
                if (dist[nx][ny] > dist[cx][cy]){
                    dist[nx][ny] = dist[cx][cy];
                    dq.push_front({nx, ny});
                }
            }
        }
    }
}