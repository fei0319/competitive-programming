#include <bits/stdc++.h>

using ll = long long int;

const int INF = 1e9;
const int MAXN = 2e5 + 19;

int n, k, f[MAXN];
ll dp[MAXN];

void solve() {
    std::cin >> n >> k;
    for (int i = 0; i <= n; ++i) {
        std::cin >> f[i];
    }

    dp[1] = k;
    for (int i = 2; i <= n; ++i) {
        // (f - k) - (f - k) / i <= dp[i - 1]
        ll l = dp[i - 1], r = 1e18;
        while (l < r) {
            ll mid = (l + r + 1) / 2;
            if ((mid - k) - (mid - k) / i <= dp[i - 1]) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        dp[i] = l;
    }

    std::function<bool(int)> check = [&](int x) -> bool {
        std::vector<int> a(f, f + x);
        std::vector<ll> s(x);
        std::sort(a.begin(), a.end());

        if (a[0] == 0) {
            return false;
        }
        for (int i = 1; i < x; ++i) {
            if (a[i] <= k) {
                return false;
            }
        }

        s[0] = a[0];
        for (int i = 1; i < x; ++i) {
            s[i] = s[i - 1] + a[i];
        }

        // value, #[=value], #[=value+1]
        auto calc = [&](int l, int r, ll v) -> int {
            int L = 0;
            // s[r] - s[l - 1] - (ll)L * (r - l + 1) <= v
            // (ll)L * (r - l + 1) >= s[r] - s[l - 1] - v
            if (s[r] - s[l - 1] - v < 0) {
                return 0;
            }
            L = (s[r] - s[l - 1] - v + (r - l + 1) - 1) / (r - l + 1);
            if (L > a[l]) {
                L = a[l];
            }

            ll rest = v - (s[r] - s[l - 1] - (ll)L * (r - l + 1));
            if (rest < 0) {
                return L;
            } else {
                if (rest) {
                    return L - 1;
                } else {
                    return L;
                }
            }
        };

        auto subcheck = [&](int l, int r, ll v) -> bool {
            ll sum = s[r] - s[l - 1] - v;

            for (int i = 1; i <= 3 && l <= r; ++i, ++l) {
                sum -= k;
                int f = std::min<ll>(sum / (r - l + 1), a[l]);
                if (f <= 0) {
                    return false;
                }
                sum -= f;
            }

            if (l <= r) {
                if (sum <= dp[r - l + 1]) {
                    return false;
                }
            }

            return true;
        };

        for (int p = 1; p <= x - 1; ++p) {
            int l = 0, r = p;
            while (l < r) {
                int mid = (l + r + 1) / 2;
                if (calc(mid, p, (ll)mid * k) >= a[mid - 1]) {
                    l = mid;
                } else {
                    r = mid - 1;
                }
            }

            if (l >= 1 && !subcheck(l, p, (ll)(l - 1) * k)) {
                return false;
            }
            if (l == 0 && !subcheck(1, p, 0)) {
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