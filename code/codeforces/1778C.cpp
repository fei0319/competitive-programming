#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e5 + 19;

int n, k, id[maxn];
char a[maxn], b[maxn];

void solve(void) {
    std::cin >> n >> k;
    std::cin >> (a + 1) >> (b + 1);

    std::vector<char> chars;
    for (int i = 1; i <= n; ++i) chars.push_back(a[i]);
    std::sort(chars.begin(), chars.end());
    chars.resize(std::unique(chars.begin(), chars.end()) - chars.begin());
    for (int i = 0; i < chars.size(); ++i) id[(int)chars[i]] = i;

    const int maxs = 1 << chars.size();
    ll ans = 0ll;
    for (int s = 0; s < maxs; ++s) {
        if (__builtin_popcount(s) > k) continue;
        ll res = 0ll;
        int last = 0;
        for (int i = 1; i <= n; ++i)
            if (a[i] == b[i] || (s & (1 << id[(int)a[i]]))) {
                res += i - last;
            } else {
                last = i;
            }
        ans = std::max(ans, res);
    }

    std::cout << ans << '\n';
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