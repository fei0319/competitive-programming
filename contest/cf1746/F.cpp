#include <bits/stdc++.h>

using ll = long long int;

constexpr int MAXN = 3e5 + 19;

constexpr int B = 30;
struct Base {
    uint64_t b[B];
    void generate(auto &&g) {
        auto d = std::uniform_int_distribution<uint64_t>(0ULL, 1ULL << 42);
        for (int i = 0; i < B; ++i) {
            b[i] = d(g);
        }
    }
    Base &operator+=(const Base &rhs) {
        for (int i = 0; i < B; ++i) {
            b[i] += rhs.b[i];
        }
        return *this;
    }
    friend Base operator+(const Base &lhs, const Base &rhs) {
        Base res;
        for (int i = 0; i < B; ++i) {
            res.b[i] = lhs.b[i] + rhs.b[i];
        }
        return res;
    }
    friend Base operator-(const Base &lhs, const Base &rhs) {
        Base res;
        for (int i = 0; i < B; ++i) {
            res.b[i] = lhs.b[i] - rhs.b[i];
        }
        return res;
    }
    uint64_t gcd() const {
        uint64_t res = b[0];
        for (int i = 1; i < B; ++i) {
            res = std::gcd(res, b[i]);
        }
        return res;
    }
} b[MAXN << 1];

int n, q, a[MAXN];

struct BIT {
    Base tr[MAXN];
    void update(int x, Base k) {
        for (; x <= n; x += x & -x) {
            tr[x] += k;
        }
    }
    Base query(int x) {
        Base res;
        std::fill(res.b, res.b + B, 0);
        for (; x; x -= x & -x) {
            res += tr[x];
        }
        return res;
    }
} mt;

std::mt19937 rng(time(nullptr));
std::map<int, int> mp;
int code(int x) {
    if (mp.contains(x)) {
        return mp[x];
    }
    int t = mp.size();
    mp[x] = t;
    b[t].generate(rng);
    return t;
}

void solve() {
    std::cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        a[i] = code(a[i]);
        mt.update(i, b[a[i]]);
    }

    while (q--) {
        int op;
        std::cin >> op;
        if (op == 1) {
            int i, x;
            std::cin >> i >> x;
            mt.update(i, b[code(x)] - b[a[i]]);
            a[i] = code(x);
        } else {
            int l, r, k;
            std::cin >> l >> r >> k;
            bool ans = (mt.query(r) - mt.query(l - 1)).gcd() % k == 0;
            std::cout << (ans ? "YES\n" : "NO\n");
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T = 1;

    while (T--) {
        solve();
    }

    return 0;
}