#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e5 + 19;

int n, cnt[maxn];
std::vector<int> val[maxn];

void solve(void) {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        int k;
        std::cin >> k;
        val[i].resize(k);
        for (int &j : val[i]) {
            std::cin >> j;
            cnt[j] = 0;
        }
    }

    for (int i = 1; i <= n; ++i)
        for (int j : val[i]) ++cnt[j];

    for (int i = 1; i <= n; ++i) {
        bool flag = 1;
        for (int j : val[i])
            if (cnt[j] < 2) {
                flag = 0;
                break;
            }
        if (flag) {
            std::cout << "Yes\n";
            return;
        }
    }
    std::cout << "No\n";
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