#include <bits/stdc++.h>
template <int m>
struct ModInt {
private:
    int raw_;
    using mint = ModInt;
    using i64 = int64_t;

public:
    ModInt() { raw_ = 0; }
    template <typename T>
    ModInt(const T &v) {
        raw_ = v % m;
    }
    int value() const { return (raw_ + m) % m; }
    mint &operator+=(const mint &rhs) {
        raw_ = (raw_ + rhs.raw_) % m;
        return *this;
    }
    mint &operator-=(const mint &rhs) {
        raw_ = (raw_ - rhs.raw_) % m;
        return *this;
    }
    mint &operator*=(const mint &rhs) {
        raw_ = (i64)raw_ * rhs.raw_ % m;
        return *this;
    }
    mint &operator/=(const mint &rhs) {
        raw_ = (i64)raw_ * qpow(rhs.raw_, m - 2) % m;
        return *this;
    }
    friend mint operator+(const mint &lhs, const mint &rhs) {
        return mint(lhs) += rhs;
    }
    friend mint operator-(const mint &lhs, const mint &rhs) {
        return mint(lhs) -= rhs;
    }
    friend mint operator*(const mint &lhs, const mint &rhs) {
        return mint(lhs) *= rhs;
    }
    friend mint operator/(const mint &lhs, const mint &rhs) {
        return mint(lhs) /= rhs;
    }
    static constexpr int mod() { return m; }
    static constexpr int qpow(int a, int b) {
        int res = 1;
        while (b) {
            if (b & 1) {
                res = (i64)res * a % m;
            }
            a = (i64)a * a % m, b >>= 1;
        }
        return res;
    }
};

using i64 = int64_t;

constexpr int MAXS = 3e5 * 4 + 19;
constexpr int MOD = 1e9 + 7;
constexpr int INF = 1e9 + 10;

using mint = ModInt<MOD>;

struct Segment {
    struct Node {
        mint ans, sum;
        int min_c;
        int tag;
    } tr[MAXS];
    void push_up(int node) {
        tr[node].ans = tr[node << 1].ans + tr[node << 1 | 1].ans;
        tr[node].sum = tr[node << 1].sum + tr[node << 1 | 1].sum;
        tr[node].min_c =
            std::min(tr[node << 1].min_c, tr[node << 1 | 1].min_c);
    }
    void push_down(int node) {
        if (tr[node].tag) {
            const int tag = tr[node].tag;
            tr[node].tag = 0;

            for (int son = node << 1; son < (node << 1) + 2; ++son) {
                tr[son].ans += tr[son].sum * tag;
                tr[son].min_c -= tag;
                tr[son].tag += tag;
            }
        }
    }
    void modify(int node, int L, int R, int l, int r, int c) {
        if (l <= L && R <= r) {
            tr[node].ans += tr[node].sum * c;
            tr[node].min_c -= c;
            tr[node].tag += c;
            return;
        }
        push_down(node);
        int mid = (L + R) / 2;
        if (l <= mid) {
            modify(node << 1, L, mid, l, r, c);
        }
        if (r > mid) {
            modify(node << 1 | 1, mid + 1, R, l, r, c);
        }
        push_up(node);
    }
    void modify(int node, int L, int R, int x,
                const std::pair<int, mint> &val) {
        if (L == R) {
            auto [c, p] = val;
            if (tr[node].min_c >= INF) {
                tr[node].min_c = 0;
            }
            tr[node].sum = (tr[node].sum * tr[node].min_c + p * c) /
                           (tr[node].min_c + c);
            tr[node].min_c += c;
            return;
        }
        push_down(node);
        int mid = (L + R) / 2;
        if (x <= mid) {
            modify(node << 1, L, mid, x, val);
        } else {
            modify(node << 1 | 1, mid + 1, R, x, val);
        }
        push_up(node);
    }
    mint query(int node, int L, int R, int l, int r) {
        if (l <= L && R <= r) {
            return tr[node].ans;
        }
        push_down(node);
        int mid = (L + R) / 2;
        mint res = 0;
        if (l <= mid) {
            res += query(node << 1, L, mid, l, r);
        }
        if (r > mid) {
            res += query(node << 1 | 1, mid + 1, R, l, r);
        }
        push_up(node);
        return res;
    }
    void adjust(int node, int L, int R) {
        if (tr[node].min_c >= 0) {
            return;
        }
        if (L == R) {
            const int c = -tr[node].min_c;
            tr[node].ans -= tr[node].sum * c;
            tr[node].min_c = INF * 2;
            tr[node].sum = 0;
            return;
        }
        push_down(node);
        int mid = (L + R) / 2;
        adjust(node << 1, L, mid);
        adjust(node << 1 | 1, mid + 1, R);
        push_up(node);
    }
} mt;

int main() {
    int n, m;
    std::cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        int a, b;
        std::cin >> a >> b;
        mt.modify(1, 1, n, i, {a + b, mint(a) / (a + b)});
    }

    for (int _ = 0; _ < m; ++_) {
        int op;
        std::cin >> op;
        if (op == 1) {
            int l, r, c;
            std::cin >> l >> r >> c;
            mt.modify(1, 1, n, l, r, c);
            mt.adjust(1, 1, n);
        } else if (op == 2) {
            int x, y;
            std::cin >> x >> y;
            std::cout << mt.query(1, 1, n, x, y).value() << '\n';
        } else {
            int p, u, v;
            std::cin >> p >> u >> v;
            mt.modify(1, 1, n, p, {u + v, mint(u) / (u + v)});
        }
    }

    return 0;
}