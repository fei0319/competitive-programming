#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 2e5 + 19;

int n, k, f[MAXN];

void solve() {
    std::cin >> n >> k;
    for (int i = 0; i <= n; ++i) {
        std::cin >> f[i];
    }

    std::function<bool(int)> check = [&](int x) -> bool {
        std::vector<int> a(f, f + x);
        std::sort(a.begin(), a.end());

        if (a[0] == 0) {
            return false;
        }
        for (int i = 1; i < x; ++i) {
            if (a[i] <= k) {
                return false;
            }
        }

        auto subcheck = [&](int p) -> bool {
            std::deque<std::pair<int, int>> q;
            auto add = [&](int v, int c) {
                if (!q.empty() && q.back().first == v) {
                    q.back().second += c;
                } else {
                    q.emplace_back(v, c);
                }
            };
            for (int i = 1; i <= p; ++i) {
                add(a[i], 1);
            }

            for (int i = 1; i <= p; ++i) {
                int r = k;
                auto [v, c] = q.back();
                q.pop_back();

                while (r >= c && v > 0) {
                    int limit = 0;
                    if (!q.empty()) {
                        limit = q.back().first;
                    }

                    int sub = std::min(r / c, v - limit);
                    r -= sub * c, v -= sub;
                    if (!q.empty() && v == q.back().first) {
                        c += q.back().second;
                        q.pop_back();
                    }
                }

                if (v == 0) {
                    return false;
                }
                if (!r) {
                    add(v, c);
                } else {
                    add(v - 1, r);
                    add(v, c - r);
                    if (v - 1 == 0) {
                        return false;
                    }
                }

                {
                    auto [v, c] = q.front();
                    q.pop_front();

                    if (c - 1 > 0) {
                        q.emplace_front(v, c - 1);
                    }
                }
            }
            return true;
        };

        for (int i = 1; i < std::min(x, 53); ++i) {
            if (!subcheck(i)) {
                return false;
            }
        }

        return true;
    };

    int l = 0, r = n + 1;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }

    std::cout << l << '\n';
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