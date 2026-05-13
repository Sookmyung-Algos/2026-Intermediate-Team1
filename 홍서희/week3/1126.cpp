#include <bits/stdc++.h>
using namespace std;

struct Point
{
    int x, y;
};

const int MAXC = 202;
const int INF = 1e9;

int sx, sy, ex, ey;
int n;

vector<vector<Point>> polys;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

bool onSegment(Point a, Point b, Point p)
{
    if ((long long)(b.x - a.x) * (p.y - a.y) !=
        (long long)(b.y - a.y) * (p.x - a.x))
        return false;

    return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

bool insidePolygon(const vector<Point> &poly, Point p)
{
    int m = poly.size();

    for (int i = 0; i < m; i++)
    {
        Point a = poly[i];
        Point b = poly[(i + 1) % m];
        if (onSegment(a, b, p))
            return false;
    }

    bool inside = false;

    for (int i = 0, j = m - 1; i < m; j = i++)
    {
        Point a = poly[i];
        Point b = poly[j];

        if ((a.y > p.y) != (b.y > p.y))
        {
            double xCross = (double)(b.x - a.x) * (p.y - a.y) / (b.y - a.y) + a.x;
            if (p.x < xCross)
                inside = !inside;
        }
    }

    return inside;
}

bool blockedPoint4(int x4, int y4)
{
    Point p{x4, y4};

    for (auto &poly : polys)
    {
        if (insidePolygon(poly, p))
            return true;
    }

    return false;
}

bool canMove(int x, int y, int dir)
{
    int nx = x + dx[dir];
    int ny = y + dy[dir];

    if (nx < 0 || nx > MAXC || ny < 0 || ny > MAXC)
        return false;

    int mx4 = x + nx;
    int my4 = y + ny;

    return !blockedPoint4(mx4, my4);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> sx >> sy;
    cin >> ex >> ey;

    sx *= 2;
    sy *= 2;
    ex *= 2;
    ey *= 2;

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int x1, y1, x2, y2, x3, y3, x4, y4;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

        vector<Point> poly;

        Point p1{x1 * 4, y1 * 4};
        Point p2{x2 * 4, y2 * 4};
        Point p3{x3 * 4, y3 * 4};
        Point p4{x4 * 4, y4 * 4};

        Point a, b;

        if (x1 == x2)
        {
            a = {x3 * 4, y4 * 4};
            b = {x4 * 4, y1 * 4};
        }
        else
        {
            a = {x4 * 4, y3 * 4};
            b = {x1 * 4, y4 * 4};
        }

        poly.push_back(p1);
        poly.push_back(p2);
        poly.push_back(p3);
        poly.push_back(a);
        poly.push_back(p4);
        poly.push_back(b);

        polys.push_back(poly);
    }

    if (sx == ex && sy == ey)
    {
        cout << 0;
        return 0;
    }

    static int dist[MAXC + 1][MAXC + 1][4];

    for (int y = 0; y <= MAXC; y++)
    {
        for (int x = 0; x <= MAXC; x++)
        {
            for (int d = 0; d < 4; d++)
            {
                dist[y][x][d] = INF;
            }
        }
    }

    deque<tuple<int, int, int>> dq;

    for (int d = 0; d < 4; d++)
    {
        dist[sy][sx][d] = 0;
        dq.push_back({sx, sy, d});
    }

    while (!dq.empty())
    {
        auto [x, y, dir] = dq.front();
        dq.pop_front();

        int cur = dist[y][x][dir];

        for (int nd = 0; nd < 4; nd++)
        {
            if (!canMove(x, y, nd))
                continue;

            int nx = x + dx[nd];
            int ny = y + dy[nd];

            int cost = cur + (dir == nd ? 0 : 1);

            if (dist[ny][nx][nd] > cost)
            {
                dist[ny][nx][nd] = cost;

                if (dir == nd)
                {
                    dq.push_front({nx, ny, nd});
                }
                else
                {
                    dq.push_back({nx, ny, nd});
                }
            }
        }
    }

    int answer = INF;

    for (int d = 0; d < 4; d++)
    {
        answer = min(answer, dist[ey][ex][d]);
    }

    cout << answer;

    return 0;
}