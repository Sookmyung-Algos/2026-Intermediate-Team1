#include <bits/stdc++.h>
using namespace std;

struct Hold
{
    int x, y;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, F;
    cin >> H >> F;

    vector<Hold> a(F);
    map<pair<int, int>, vector<int>> bucket;

    for (int i = 0; i < F; i++)
    {
        cin >> a[i].x >> a[i].y;

        int bx = a[i].x / 1000;
        int by = a[i].y / 1000;

        bucket[{bx, by}].push_back(i);
    }

    queue<int> q;
    vector<int> dist(F, -1);

    for (int i = 0; i < F; i++)
    {
        if (a[i].y <= 1000)
        {
            dist[i] = 1;
            q.push(i);
        }
    }

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();

        if (a[cur].y >= H - 1000)
        {
            cout << dist[cur] << '\n';
            return 0;
        }

        int bx = a[cur].x / 1000;
        int by = a[cur].y / 1000;

        for (int dx = -1; dx <= 1; dx++)
        {
            for (int dy = -1; dy <= 1; dy++)
            {
                pair<int, int> near_key = {bx + dx, by + dy};

                if (bucket.find(near_key) == bucket.end())
                    continue;

                for (int nxt : bucket[near_key])
                {
                    if (dist[nxt] != -1)
                        continue;

                    long long X = a[cur].x - a[nxt].x;
                    long long Y = a[cur].y - a[nxt].y;

                    if (X * X + Y * Y <= 1000LL * 1000LL)
                    {
                        dist[nxt] = dist[cur] + 1;
                        q.push(nxt);
                    }
                }
            }
        }
    }

    cout << -1 << '\n';
    return 0;
}