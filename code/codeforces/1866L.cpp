#include <bits/stdc++.h>

using ll = long long int;

const int MAXM = 2e3 + 19;

int n, m;
ll ans[MAXM];

ll solve(int m) {
    ll res = 0;

    int now = m, prev = 1;
    auto check = [&](int x) { return now + x * m > prev + x; };
    do {
        int l = 0, r = (n - now) / m;
        while (l < r) {
            int mid = (l + r) / 2;
            if (check(mid)) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        r = (n - now) / m;

        if (check(r)) {
            res += ll(r - l + 1) * now + (ll)m * (l + r) * (r - l + 1) / 2;
        }

        prev += (n - now) / m + 1;
        now += (n - now) / m * m + m;
        now = (now - 1) % n + 1;
    } while (now != m);

    return res;
}

int main() {
    std::cin >> n >> m;
    for (int i = 2; i <= std::min(m, n); ++i) {
        ans[i] = solve(i);
    }

    std::cout << std::max_element(ans + 1, ans + 1 + m) - ans << '\n';
    return 0;
}