#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<ll> makeSums(
    const vector<ll>& numbers,
    int left,
    int right,
    ll mod
) {
    vector<ll> sums = {0};

    for (int i = left; i < right; ++i) {
        int size = sums.size();

        for (int j = 0; j < size; ++j) {
            sums.push_back((sums[j] + numbers[i]) % mod);
        }
    }

    return sums;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ll M;
    cin >> N >> M;

    vector<ll> numbers(N);

    for (ll& number : numbers) {
        cin >> number;
        number %= M;
    }

    int mid = N / 2;

    vector<ll> leftSums = makeSums(numbers, 0, mid, M);
    vector<ll> rightSums = makeSums(numbers, mid, N, M);

    sort(rightSums.begin(), rightSums.end());

    ll answer = 0;

    for (ll leftSum : leftSums) {
        ll limit = M - 1 - leftSum;

        auto it = upper_bound(
            rightSums.begin(),
            rightSums.end(),
            limit
        );

        if (it != rightSums.begin()) {
            --it;
            answer = max(answer, leftSum + *it);
        }
    }

    cout << answer << '\n';
}
