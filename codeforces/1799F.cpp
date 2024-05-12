#include <bits/stdc++.h>

using ll = long long int;

const ll INF = 1e18;

void solve() {
    int n, b, k1, k2;
    std::cin >> n >> b >> k1 >> k2;
    std::vector<int> a(n);
    for (int &i : a) {
        std::cin >> i;
    }
    std::sort(a.begin(), a.end());

    ll base = 0;
    while (!a.empty() && (k1 && k2) && a.back() >= 2 * b - 1) {
        base += (a.back() + 1) / 2 - b;
        a.pop_back();
        k1 -= 1;
        k2 -= 1;
    }

    ll ans = INF;
    // k1 + k2 - t <= a.size()
    // t >= k1 + k2 - a.size()
    for (int t = std::max<int>(0, k1 + k2 - a.size()); t <= std::min(k1, k2);
         ++t) {
        std::vector<int> c = std::vector<int>(a.end() - (k1 + k2 - t), a.end());

        ll res = std::accumulate(a.begin(), a.end() - (k1 + k2 - t), 0LL);
        for (int i = c.size() - t; i < c.size(); ++i) {
            res += std::max((c[i] + 1) / 2 - b, 0);
        }
        c = std::vector<int>(c.begin(), c.end() - t);

        std::vector<int> d;
        for (int i : c) {
            res += std::max(i - b, 0);
            d.push_back((i + 1) / 2 - std::max(i - b, 0));
        }
        std::sort(d.begin(), d.end());
        for (int i = 0; i < k1 - t; ++i) {
            res += d[i];
        }

        ans = std::min(ans, res);
    }

    std::cout << base + ans << '\n';
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