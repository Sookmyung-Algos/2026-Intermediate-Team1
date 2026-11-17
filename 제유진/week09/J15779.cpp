
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<string> phone(n);

        for (int i = 0; i < n; i++) {
            cin >> phone[i];
        }

        sort(phone.begin(), phone.end());

        bool consistent = true;

        for (int i = 0; i < n - 1; i++) {
            if (phone[i + 1].find(phone[i]) == 0) {
                consistent = false;
                break;
            }
        }

        cout << (consistent ? "YES" : "NO") << '\n';
    }

    return 0;
}
