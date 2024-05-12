#include <bits/stdc++.h>

using ll = long long int;

void solve() {
    std::string s;
    std::cin >> s;

    auto match = [&](char a, char b) {
        if (a == '?' || b == '?') {
            return true;
        }
        return a == b;
    };

    int ans = 0;
    int n = s.size();
    for (int L = 1; L * 2 <= n; ++L) {
        int num = 0;
        for (int i = 0; i + 1 < L; ++i) {
            num += match(s[i], s[i + L]);
        }

        for (int i = 0; i + L * 2 - 1 < n; ++i) {
            num += match(s[i + L - 1], s[i + L * 2 - 1]);
            if (num == L) {
                ans = L;
                break;
            }
            num -= match(s[i], s[i + L]);
        }
    }

    std::cout << ans * 2 << '\n';
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