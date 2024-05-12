#include <bits/stdc++.h>

using ll = long long int;

std::string s;
int ok[26][26];

void solve(void) {
    int n;
    std::cin >> n;
    std::cin >> s;
    for (int i = 0; i < 26; ++i)
        for (int j = 0; j < 26; ++j)
            ok[i][j] = 0;
    for (int i = 0; i + 1 < n; ++i) {
        ++ok[s[i] - 'a'][s[i + 1] - 'a'];
        if (i + 2 < n && s[i] == s[i + 1] && s[i] == s[i + 2])
            ++i;
    }
    for (int i = 0; i < 26; ++i)
        for (int j = 0; j < 26; ++j) {
            if (ok[i][j] > 1) {
                std::cout << "YES\n";
                return;
            }
        }
    std::cout << "NO\n";
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