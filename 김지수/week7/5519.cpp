#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<ll> makeSums(int left, int right) {
    vector<ll> sums = {0};

    for (int value = left; value <= right; ++value) {
        int size = sums.size();

        for (int i = 0; i < size; ++i) {
            sums.push_back(sums[i] + value);
        }
    }

    return sums;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    ll total = 1LL * N * (N + 1) / 2;

    if (total % 2 == 1) {
        cout << 0 << '\n';
        return 0;
    }

    // N이 포함된 쪽의 나머지 원소 합
    ll target = total / 2 - N;

    if (target < 0) {
        cout << 0 << '\n';
        return 0;
    }

    int mid = (N - 1) / 2;

    vector<ll> leftSums = makeSums(1, mid);
    vector<ll> rightSums = makeSums(mid + 1, N - 1);

    sort(rightSums.begin(), rightSums.end());

    ll answer = 0;

    for (ll leftSum : leftSums) {
        ll need = target - leftSum;

        auto lower = lower_bound(rightSums.begin(), rightSums.end(), need);
        auto upper = upper_bound(rightSums.begin(), rightSums.end(), need);

        answer += upper - lower;
    }

    cout << answer << '\n';
}
