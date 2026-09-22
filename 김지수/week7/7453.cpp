#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> A(N), B(N), C(N), D(N);

    for (int i = 0; i < N; ++i) {
        cin >> A[i] >> B[i] >> C[i] >> D[i];
    }

    vector<int> ab;
    vector<int> cd;

    ab.reserve(1LL * N * N);
    cd.reserve(1LL * N * N);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            ab.push_back(A[i] + B[j]);
            cd.push_back(C[i] + D[j]);
        }
    }

    sort(ab.begin(), ab.end());
    sort(cd.begin(), cd.end());

    int left = 0;
    int right = static_cast<int>(cd.size()) - 1;
    ll answer = 0;

    while (left < static_cast<int>(ab.size()) && right >= 0) {
        ll sum = static_cast<ll>(ab[left]) + cd[right];

        if (sum < 0) {
            ++left;
        } else if (sum > 0) {
            --right;
        } else {
            int leftValue = ab[left];
            int rightValue = cd[right];

            ll leftCount = 0;
            ll rightCount = 0;

            while (
                left < static_cast<int>(ab.size()) &&
                ab[left] == leftValue
            ) {
                ++leftCount;
                ++left;
            }

            while (right >= 0 && cd[right] == rightValue) {
                ++rightCount;
                --right;
            }

            answer += leftCount * rightCount;
        }
    }

    cout << answer << '\n';
}
