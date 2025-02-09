#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e6 + 19;

int n, s[maxn];
char b[maxn];

bool can_zero() {
    for (int i = 1; i <= n; ++i)
        if (s[i] < 0) return false;
    std::cout << "0\n";
    return true;
}

bool ok(int l, int r) {
    std::reverse(b + l, b + r + 1);
    int s = 0;
    for (int i = 1; i <= n; ++i) {
        if (b[i] == '(') ++s;
        else
            --s;
        if (s < 0) return false;
    }
    return true;
}

bool can_one() {
    int l = 0, r = n;
    for (int i = 1; i <= n; ++i) {
        if (s[i] < 0) break;
        if (s[i] > s[l]) l = i;
    }
    for (int i = n; i >= 1; --i) {
        if (s[i] < 0) break;
        if (s[i] > s[r]) r = i;
    }
    if (!ok(l + 1, r)) return false;
    std::cout << "1\n";
    std::cout << l + 1 << ' ' << r << '\n';
    return true;
}

void solve(void) {
    std::cin >> n >> (b + 1);
    n <<= 1;
    for (int i = 1; i <= n; ++i) {
        s[i] = s[i - 1] + (b[i] == '(' ? 1 : -1);
    }

    if (can_zero()) return;
    if (can_one()) return;

    int mx = 1;
    for (int i = 1; i <= n; ++i)
        if (s[i] > s[mx]) mx = i;
    std::cout << "2\n";
    std::cout << "1 " << mx << '\n';
    std::cout << mx + 1 << ' ' << n << '\n';
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