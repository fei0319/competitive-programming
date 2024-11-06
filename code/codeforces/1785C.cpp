#include <bits/stdc++.h>

using i64 = long long int;

constexpr int MOD = 998244353;

template <typename Tp>
Tp qpow(Tp a, int b) {
    Tp res = 1;
    while (b) {
        if (b & 1) res *= a;
        a *= a, b >>= 1;
    }
    return res;
}

int norm(int x) {
    if (x < 0) {
        x += MOD;
    }
    if (x >= MOD) {
        x -= MOD;
    }
    return x;
}

struct Z {
    int x;
    Z(int x = 0) : x(norm(x)) {}
    Z(i64 x) : x(norm(x % MOD)) {}
    int val() const { return x; }
    Z operator-() const { return Z(norm(MOD - x)); }
    Z inv() const {
        assert(x != 0);
        return qpow(*this, MOD - 2);
    }
    Z &operator*=(const Z &rhs) {
        x = i64(x) * rhs.x % MOD;
        return *this;
    }
    Z &operator+=(const Z &rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    Z &operator-=(const Z &rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    Z &operator/=(const Z &rhs) { return *this *= rhs.inv(); }
    friend Z operator*(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res *= rhs;
        return res;
    }
    friend Z operator+(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res += rhs;
        return res;
    }
    friend Z operator-(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res -= rhs;
        return res;
    }
    friend Z operator/(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res /= rhs;
        return res;
    }
    friend std::istream &operator>>(std::istream &is, Z &a) {
        i64 v;
        is >> v;
        a = Z(v);
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const Z &a) {
        return os << a.val();
    }
};

constexpr int maxn = 2e5 + 19;
int n, b[maxn];
std::pair<int, int> a[maxn];
int fa[maxn];
i64 ans[maxn];

int getf(int node) {
    return fa[node] == node ? node : fa[node] = getf(fa[node]);
}

struct BIT {
    i64 tr[maxn];
    void clear(int n) {
        for (int i = 1; i <= n; ++i) tr[i] = 0;
    }
    void update(int x, i64 k) {
        for (; x <= n; x += x & -x) tr[x] += k;
    }
    i64 query(int x) {
        i64 res = 0;
        for (; x; x -= x & -x) res += tr[x];
        return res;
    }
    i64 query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
} T;

struct sBIT {
    BIT t;
    void clear(int n) { t.clear(n); }
    void update(int l, int r, i64 k) {
        if (l > r) return;
        t.update(l, k);
        t.update(r + 1, -k);
    }
    i64 query(int x) { return t.query(x); }
} con;

void solve(void) {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i].first;
        a[i].second = i;
    }

    std::sort(a + 1, a + 1 + n);
    int last = 0;
    i64 tot = 0;

    T.clear(n), con.clear(n);
    for (int i = 1; i <= n; ++i) {
        T.update(i, 1);

        if (a[i].first > last + 1) {
            tot += a[i].first - last - 1;
            con.update(i, i, a[i].first - last - 1);

            ++last;

            b[a[i].second] = i;
            fa[i] = i + 1;
        } else if (a[i].first == last + 1) {
            ++last;

            b[a[i].second] = i;
            fa[i] = i + 1;
        } else {
            b[a[i].second] = i;
            fa[i] = i;
        }
    }
    fa[n + 1] = n + 1;

    for (int i = n; i >= 1; --i) {
        ans[i] = tot;
        int pos = b[i];
        int next = getf(pos);
        //	std::cout << next << '\n';
        tot += T.query(pos + 1, next - 1);
        T.update(pos, -1);
        con.update(pos + 1, next - 1, 1);

        tot -= con.query(pos);

        if (next != n + 1) fa[next] = next + 1;
    }

    for (int i = 1; i <= n; ++i) std::cout << ans[i] << ' ';
    std::cout << '\n';
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