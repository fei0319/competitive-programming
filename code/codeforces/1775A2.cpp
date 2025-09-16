#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e6 + 19;

std::string s;
int prev[maxn][2], suff[maxn][2];

void out(int a, int b, int n) {
    for (int i = 1; i < a; ++i) std::cout << s[i - 1];
    std::cout << ' ';
    for (int i = a; i < b; ++i) std::cout << s[i - 1];
    std::cout << ' ';
    for (int i = b; i <= n; ++i) std::cout << s[i - 1];
    std::cout << '\n';
}

void solve(void) {
    std::cin >> s;
    int n = s.length();

    suff[n + 1][0] = suff[n + 1][1] = 0;

    for (int i = 1; i <= n; ++i) {
        prev[i][0] = prev[i - 1][0];
        prev[i][1] = prev[i - 1][1];
        prev[i][s[i - 1] - 'a'] = i;
    }
    for (int i = n; i >= 1; --i) {
        suff[i][0] = suff[i + 1][0];
        suff[i][1] = suff[i + 1][1];
        suff[i][s[i - 1] - 'a'] = i;
    }

    for (int i = 1; i <= n; ++i)
        if (s[i - 1] != s[0] && suff[i + 1][s[0] - 'a']) {
            out(i, suff[i + 1][s[0] - 'a'], n);
            return;
        }

    if (s[0] == s[n - 1]) {
        out(2, 3, n);
        return;
    }

    int m = 1;
    while (s[m] == s[m - 1]) ++m;
    if (s[0] == 'a') {
        if (m >= 2) out(m, m + 1, n);
        else out(m + 1, n, n);
    } else {
        if (m >= 2) out(2, m + 1, n);
        else out(m + 1, m + 2, n);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}