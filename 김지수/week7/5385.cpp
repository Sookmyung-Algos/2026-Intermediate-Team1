#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<ll> makeSums(const vector<ll>& cards, int left, int right) {
    vector<ll> sums = {0};

    for (int i = left; i < right; ++i) {
        int size = sums.size();

        for (int j = 0; j < size; ++j) {
            sums.push_back(sums[j] + cards[i]);
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

    vector<ll> cards(N);

    for (ll& card : cards) {
        cin >> card;
    }

    int mid = N / 2;

    vector<ll> leftSums = makeSums(cards, 0, mid);
    vector<ll> rightSums = makeSums(cards, mid, N);

    sort(rightSums.begin(), rightSums.end());

    ll answer = 0;

    for (ll leftSum : leftSums) {
        ll need = M - leftSum;

        auto lower = lower_bound(rightSums.begin(), rightSums.end(), need);
        auto upper = upper_bound(rightSums.begin(), rightSums.end(), need);

        answer += upper - lower;
    }

    // 문제에서는 카드를 한 장 이상 뽑아야 한다.
    if (M == 0) {
        --answer;
    }

    cout << answer << '\n';
}
