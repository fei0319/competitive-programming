#include <bits/stdc++.h>

using ll = long long int;

const char *t = "codeforces";

void solve(void) {
    std::string s;
    std::cin >> s;
    int ans = 0;
    for (int i = 0; i < (int)s.length(); ++i) {
        if (s[i] != t[i]) {
            ++ans;
        }
    }
    std::cout << ans << std::endl;
}

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}