#include <bits/stdc++.h>

using ll = long long int;

const int MAXD = 1e3 + 19;

std::bitset<MAXD * 2> dp[MAXD];

void solve(void) {
    int n, d;
    std::cin >> n >> d;

    std::vector<int> a(n);
    int cnt = 0;
    for (int &i : a) {
        std::cin >> i;
        if (i > d / 2) ++cnt;
    }

    if (cnt >= 2) {
        std::cout << "NO\n";
        return;
    }

    std::sort(a.begin(), a.end());
    for (int i = 0; i <= d / 2; ++i) {
        dp[i].reset();
    }
    dp[0].set(0);
    for (int i = 0; i < a.size(); ++i) {
        int t = a[i];
        for (int j = d / 2; j >= 0; --j) {
            dp[j] |= dp[j] << t;
            if (j >= t) {
                dp[j] |= dp[j - t];
            }
        }
    }

    if (cnt == 1) {
        int p = a[a.size() - 1], q = a[a.size() - 2];
        if (dp[d - p].any() && q <= d - p) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
        return;
    }

    for (int i = a.back(); i <= d / 2; ++i) {
        if (dp[i][d - i]) {
            std::cout << "YES\n";
            return;
        }
    }
    std::cout << "NO\n";
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