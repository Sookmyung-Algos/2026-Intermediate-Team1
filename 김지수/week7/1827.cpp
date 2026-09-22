#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ll M;
    cin >> N >> M;

    vector<ll> score(N + 1);
    score[0] = 0;  // 다트를 던지지 않는 경우

    for (int i = 1; i <= N; ++i) {
        cin >> score[i];
    }

    vector<ll> pairSums;
    pairSums.reserve(1LL * (N + 1) * (N + 2) / 2);

    for (int i = 0; i <= N; ++i) {
        for (int j = i; j <= N; ++j) {
            pairSums.push_back(score[i] + score[j]);
        }
    }

    sort(pairSums.begin(), pairSums.end());

    ll answer = 0;

    for (ll first : pairSums) {
        if (first > M) {
            break;
        }

        auto it = upper_bound(
            pairSums.begin(),
            pairSums.end(),
            M - first
        );

        if (it == pairSums.begin()) {
            continue;
        }

        --it;
        answer = max(answer, first + *it);
    }

    cout << answer << '\n';
}
