#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 2e5 + 19;

int n, a[MAXN], cnt[MAXN], b[MAXN];

void solve() {
    std::cin >> n;
    std::fill(cnt, cnt + n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        cnt[a[i]] += 1;
    }

    auto check = [&](int x) {
        for (int i = 0; i <= x + 1; ++i) {
            b[i] = cnt[i];
        }
        std::sort(b, b + x);
        if (b[0] == 0) {
        	return false;
        }
        for (int j = 1; j < x; ++j) {
            if (b[j] < 2) {
                return false;
            }
        }
        return true;
    };

    int l = 0, r = n;
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