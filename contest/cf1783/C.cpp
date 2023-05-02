#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e6 + 19;

int n, m, a[maxn];

void solve(void) {
    std::cin >> n >> m;
    int prem = m;
    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];
    std::multiset<int> s;
    for (int i = 1; i <= n; ++i)
        s.insert(a[i]);
    int now = 0;
    while (s.size() && m >= *s.begin())
        m -= *s.begin(), s.erase(s.begin()), ++now;
    //	std::cout << n - now + 1 << '\n';
    if (now < n) {
        int x = now;
        now = 1;
        m = prem - a[x + 1];
        for (int i = 1; i <= n; ++i)
            if (i != x + 1)
                s.insert(a[i]);
        while (s.size() && m >= *s.begin())
            m -= *s.begin(), s.erase(s.begin()), ++now;
        if (m < 0 || now < x)
            now = x;
        else
            now = x + 1;
    }
    std::cout << n - now + 1 << '\n';
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