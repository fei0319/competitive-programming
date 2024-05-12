#include <bits/stdc++.h>

using ll = long long int;

void solve() {
    int n, m;
    std::string s;
    std::cin >> n >> m >> s;

    int cnt = std::count(s.begin(), s.end(), '1');
    if ((ll)m * cnt % n != 0) {
        std::cout << "-1\n";
        return;
    }

    int t = (ll)m * cnt / n;
    int now = m - 1, val = std::count(s.begin(), s.begin() + m, '1');

    auto answer = [](int x, int y) {
        std::cout << x + 1 << ' ' << y + 1 << '\n';
    };

    for (; now < n; ++now) {
        if (val == t) {
            std::cout << "1\n";
            answer(now - m + 1, now);
            return;
        }
        val -= (s[now - m + 1] == '1');
        if (now + 1 < n) {
            val += (s[now + 1] == '1');
        }
    }

    now = m - 1, val = std::count(s.begin(), s.begin() + m, '1');
    for (; now >= 0; --now) {
        if (val == t) {
            std::cout << "2\n";
            answer(0, now);
            answer(n - m + now + 1, n - 1);
            return;
        }
        val -= (s[now] == '1');
        val += (s[n - m + now] == '1');
    }
    assert(false);
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