#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e6 + 19, mod = 998244353;

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1)
            res = (ll)res * a % mod;
        a = (ll)a * a % mod, b >>= 1;
    }
    return res;
}

int n;
char a[maxn], b[maxn];

struct Node {
    int x, y;
    Node(int _x = 0, int _y = 0) {
        x = _x, y = _y;
    }
    void out() {
        std::cout << x << ' ' << y << '\n';
    }
} f[maxn];

Node operator*(int a, Node b) {
    return Node((ll)a * b.x % mod, (ll)a * b.y % mod);
}
Node operator*(Node b, int a) {
    return Node((ll)a * b.x % mod, (ll)a * b.y % mod);
}
Node operator-(Node a, Node b) {
    return Node((a.x - b.x) % mod, (a.y - b.y) % mod);
}
Node operator-(Node a, int b) {
    return Node(a.x, (a.y - b) % mod);
}

void solve(void) {
    std::cin >> n;
    std::cin >> (a + 1) >> (b + 1);

    int k = 0;
    for (int i = 1; i <= n; ++i)
        if (a[i] != b[i])
            ++k;

    f[n] = Node(1, 0), f[n - 1] = Node(1, -1);
    for (int i = n - 1; i >= 1; --i) {
        f[i - 1] = (n * f[i] - (n - i) * f[i + 1] - n) * qpow(i, mod - 2);
    }

    int base = -1ll * f[0].y * qpow(f[0].x, mod - 2) % mod,
        ans = ((ll)f[k].x * base + f[k].y) % mod;

    std::cout << (ans + mod) % mod << '\n';
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