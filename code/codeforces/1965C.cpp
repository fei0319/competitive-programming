#include <bits/stdc++.h>

using ll = long long int;

void solve() {
    int n;
    std::string s;

    std::cin >> n;
    std::cin >> s;

    if (s[0] == '1') {
        for (auto &i : s) {
            if (i == '0')
                i = '1';
            else
                i = '0';
        }
    }

    int now = n * 2, l = now, r = now, d = +1;
    for (int i = 1; i < n; ++i) {
        if ((s[i] == '1') != (now & 1)) {
            now += d;
        } else {
            d *= -1;
        }
        l = std::min(l, now);
        r = std::max(r, now);
    }

    std::cout << r - l + 1 << '\n';
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