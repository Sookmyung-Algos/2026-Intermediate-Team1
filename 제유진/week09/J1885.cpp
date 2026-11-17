
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<string> phone(N);

        for (int i = 0; i < N; i++) {
            cin >> phone[i];
        }

        // 사전순 정렬
        sort(phone.begin(), phone.end());

        bool consistent = true;

        // 인접한 전화번호끼리 접두사 확인
        for (int i = 0; i < N - 1; i++) {
            if (phone[i + 1].find(phone[i]) == 0) {
                consistent = false;
                break;
            }
        }

        cout << (consistent ? "YES" : "NO") << '\n';
    }

    return 0;
}
