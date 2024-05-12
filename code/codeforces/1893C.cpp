#include <bits/stdc++.h>

using ll = long long int;

struct Node {
    int n;
    ll l, r;
    std::vector<std::pair<ll, ll>> a;
};

void solve(void) {
    int m;
    std::cin >> m;

    ll l = 0, r = 0;
    ll bonus = 0;
    std::vector<Node> s(m);
    std::map<ll, std::pair<ll, ll>> mt;
    // <# at least choose, # can be chose without punishment>
    for (auto &i : s) {
        std::cin >> i.n >> i.l >> i.r;
        l += i.l, r += i.r;
        int n = i.n;
        i.a.resize(n);

        ll tot = 0;
        for (int j = 0; j < n; ++j) {
            std::cin >> i.a[j].first;
        }
        for (int j = 0; j < n; ++j) {
            std::cin >> i.a[j].second;
            tot += i.a[j].second;
        }

        for (auto [a, c] : i.a) {
            if (mt.count(a) == 0) {
                mt[a] = std::make_pair(0ll, 0ll);
            }
            if (i.l > tot - c) {
                mt[a].first += i.l - (tot - c);
            } else {
                mt[a].second += std::min(tot - c, i.r) - i.l;
            }
            mt[a].second -= i.r - i.l;
        }
        bonus += i.r - i.l;
    }

    ll ans = 1e18, num_between_l_r = 0;
    for (auto [a, p] : mt) {
        if (a < l || a > r) {
            continue;
        }
        num_between_l_r += 1;
        p.second += bonus;
        // std::cout << a << ' ' << p.first << ' ' << p.second << '\n';
        ll res = p.first;
        ll need = a - l;
        if (need > p.second) {
            res += need - p.second;
        }
        ans = std::min(ans, res);
    }
    if (num_between_l_r < r - l + 1) {
        ans = 0;
    }

    std::cout << ans << '\n';
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