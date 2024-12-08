#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e6 + 19;

int n, L, a[maxn];
int s1[maxn], s2[maxn];

ll cal(int *a, int *b) {
    int ptr = 1;
    ll ans = 1e18;
    for (int i = 1; i <= n; ++i) {
        while (b[ptr] < a[i] && ptr + 1 <= n) ++ptr;
        if (b[ptr] < a[i]) break;
        ans = std::min(ans, (ll)b[ptr] - a[i]);
    }
    return ans;
}

void solve(void) {
    std::cin >> n >> L;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        s1[i] = a[i];
        s2[i] = L - a[n - i + 1];
    }
    std::cout << 2ll * (L + std::min(cal(s1, s2), cal(s2, s1)));
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    T = 1;

    while (T--) {
        solve();
    }

    return 0;
}