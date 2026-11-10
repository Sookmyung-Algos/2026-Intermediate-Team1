#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    string s;
    cin >> s;
    int n = s.size();
 
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
 
    int L = pi[n - 1];
    if (L == 0) {
        cout << "Just a legend\n";
        return 0;
    }
 
    int mx = 0;
    for (int i = 0; i < n - 1; i++) mx = max(mx, pi[i]);
 
    if (mx >= L) {
        cout << s.substr(0, L) << "\n";
    } else if (pi[L - 1] > 0) {
        cout << s.substr(0, pi[L - 1]) << "\n";
    } else {
        cout << "Just a legend\n";
    }
    return 0;
}
