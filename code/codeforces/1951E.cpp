#include <bits/stdc++.h>

using ll = long long int;

bool is_palindrome(std::string s) {
    int l = 0, r = s.size() - 1;
    while (l < r) {
        if (s[l] != s[r]) {
            return false;
        }
        l += 1, r -= 1;
    }
    return true;
}

constexpr int MAXN = 1e6 + 19;
constexpr int T = 3;

std::mt19937 rng(time(nullptr));

const int p[] = {998244353, 1004535989, int(1e9) + 9};
int b[T][MAXN];
int H[T][MAXN], R[T][MAXN];

void solve() {
    std::string s;
    std::cin >> s;

    if (!is_palindrome(s)) {
        std::cout << "YES\n";
        std::cout << 1 << '\n';
        std::cout << s << '\n';
        return;
    }

    int n = s.size();
    for (int i = 0; i + 1 < n; ++i) {
        if (s[i] != s[0] && s[i + 1] != s[n - 1]) {
            std::cout << "YES\n";
            std::cout << 2 << '\n';
            std::cout << s.substr(0, i + 1) << ' ' << s.substr(i + 1)
                      << '\n';
            return;
        }
    }

    s = ' ' + s;

    std::uniform_int_distribution<int> rnd(9, int(1e9));
    for (int i = 0; i < T; ++i) {
        b[i][0] = 1;
        b[i][1] = rnd(rng);
        for (int j = 2; j <= n; ++j) {
            b[i][j] = (ll)b[i][j - 1] * b[i][1] % p[i];
        }
    }
    auto make_hash = [&](int h[T][MAXN]) {
        for (int i = 0; i < T; ++i) {
            for (int j = 1; j <= n; ++j) {
                h[i][j] = ((ll)h[i][j - 1] * b[i][1] + s[j]) % p[i];
            }
        }
    };

    auto get = [&](int t, int h[T][MAXN], int l, int r) -> int {
        return ((h[t][r] - (ll)h[t][l - 1] * b[t][r - l + 1]) % p[t] +
                p[t]) %
               p[t];
    };

    make_hash(H);
    std::reverse(s.begin() + 1, s.end());
    make_hash(R);
    std::reverse(s.begin() + 1, s.end());

    auto check = [&](int l, int r) {
        for (int t = 0; t < T; ++t) {
            if (get(t, H, l, r) != get(t, R, n - r + 1, n - l + 1)) {
                return true;
            }
        }
        return false;
    };

    for (int i = 1; i < n; ++i) {
        if (check(1, i) && check(i + 1, n)) {
            std::cout << "YES\n";
            std::cout << 2 << '\n';
            std::cout << s.substr(1, i) << ' ' << s.substr(i + 1) << '\n';
            return;
        }
    }

    std::cout << "NO\n";
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