#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e5 + 19;

int n, a[maxn];
ll s[maxn];

int find_first_zero() {
    for (int i = 1; i <= n; ++i)
        if (a[i] == 0)
            return i;
    return -1;
}

int count_zero(int n) {
    int res = 0;
    for (int i = 1; i <= n; ++i)
        if (s[i] == 0)
            ++res;
    return res;
}

int count_dep(int l, int r) {
    std::sort(s + l, s + r + 1);
    int ans = 0;
    for (int i = l, cur; i <= r; ++i) {
        if (i == l || s[i] != s[i - 1])
            cur = 1;
        else
            ++cur;
        ans = std::max(ans, cur);
    }
    return ans;
}

void solve(void) {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        s[i] = s[i - 1] + a[i];
    }
    int l = find_first_zero(), r;
    if (l == -1)
        std::cout << count_zero(n) << std::endl;
    else {
        int ans = count_zero(l - 1);
        for (; l <= n; l = r + 1) {
            r = l;
            while (r + 1 <= n && a[r + 1] != 0)
                ++r;
            ans += count_dep(l, r);
        }
        std::cout << ans << std::endl;
    }
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