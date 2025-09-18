#include <bits/stdc++.h>

template <typename T, size_t S, size_t A = sizeof(T)>
class Rc {
    struct Block {
        std::byte data[A];
        int ref;
    };
    static int head;
    static Block pool[S];
    static int alloc() {
        int x = head;
        head += pool[head].ref + 1;
        return x;
    }
    static void free(int idx) {
        reinterpret_cast<T *>(pool[idx].data)->~T();
        pool[idx].ref = head - idx - 1;
        head = idx;
    }

    int idx{};
    void release(int idx) {
        if (idx) {
            if (--pool[idx].ref == 0) {
                free(idx);
            }
        }
    }
    explicit Rc(int x) : idx(x) {}

public:
    Rc() = default;
    Rc(const Rc &other) {
        idx = other.idx;
        pool[idx].ref += 1;
    }
    Rc(Rc &&other) {
        idx = other.idx;
        other.idx = 0;
    }
    ~Rc() { release(idx); }
    Rc &operator=(const Rc &other) {
        if (this != &other) {
            release(idx);
            idx = other.idx;
            pool[idx].ref += 1;
        }
        return *this;
    }
    Rc &operator=(Rc &&other) {
        if (this != &other) {
            release(idx);
            idx = other.idx;
            other.idx = 0;
        }
        return *this;
    }
    template <typename... Args>
    static Rc make(Args &&...args) {
        int idx = alloc();
        new (pool[idx].data) T(std::forward<Args>(args)...);
        pool[idx].ref = 1;
        return Rc{idx};
    }

    T &operator*() const { return *reinterpret_cast<T *>(pool[idx].data); }
    T *operator->() const { return reinterpret_cast<T *>(pool[idx].data); }
    explicit operator bool() const { return idx; }
};
template <typename T, size_t S, size_t A>
constinit int Rc<T, S, A>::head = 1;
template <typename T, size_t S, size_t A>
constinit Rc<T, S, A>::Block Rc<T, S, A>::pool[S];

template <int m>
class ModInt {
    int raw;
    using mint = ModInt;
    using i64 = int64_t;

public:
    ModInt() : raw(0) {}
    ModInt(const auto &v) {
        raw = v % m;
        if (raw < 0) raw += m;
    }
    int operator()() const { return raw; }
    mint &operator+=(const mint &rhs) {
        raw += rhs.raw;
        if (raw >= m) raw -= m;
        return *this;
    }
    mint &operator-=(const mint &rhs) {
        raw -= rhs.raw;
        if (raw < 0) raw += m;
        return *this;
    }
    mint &operator*=(const mint &rhs) {
        raw = (i64)raw * rhs.raw % m;
        return *this;
    }
    mint &operator/=(const mint &rhs) { return *this *= qpow(rhs, m - 2); }

#define DOP(op)                                                           \
    friend mint operator op(const mint &lhs, const mint &rhs) {           \
        return mint{lhs} op## = rhs;                                      \
    }
    DOP(+)
    DOP(-)
    DOP(*)
    DOP(/)
#undef DOP

    static constexpr int mod() { return m; }
    static mint qpow(mint a, i64 b) {
        mint res = 1;
        while (b) {
            if (b & 1) res *= a;
            a *= a, b >>= 1;
        }
        return res;
    }
};

using mint = ModInt<static_cast<int>(1e9) + 7>;

constexpr int S = 1e7;
struct Node {
    Rc<const Node, S, 16> ls, rs;
    mint sum, tag;
};
using NodeRc = Rc<const Node, S, 16>;

NodeRc push_up(const NodeRc &x, const NodeRc &ls, const NodeRc &rs) {
    return NodeRc::make(ls, rs, (ls->sum + rs->sum) * x->tag, x->tag);
}
auto multiply(const NodeRc &x, int L, int R, int l, int r,
              mint w) -> NodeRc {
    if (l <= L && R <= r) {
        return NodeRc::make(x->ls, x->rs, x->sum * w, x->tag * w);
    }
    const int mid = L + (R - L) / 2;
    NodeRc ls = x->ls, rs = x->rs;
    if (l <= mid) ls = multiply(ls, L, mid, l, r, w);
    if (r > mid) rs = multiply(rs, mid + 1, R, l, r, w);
    return push_up(x, ls, rs);
}
auto insert(const NodeRc &x, mint tag, int L, int R, int p,
            mint w) -> NodeRc {
    if (L == R) {
        return NodeRc::make(NodeRc{}, NodeRc{}, w / tag, mint{});
    }
    const int mid = L + (R - L) / 2;
    NodeRc ls = x->ls, rs = x->rs;
    if (p <= mid) ls = insert(x->ls, tag * x->tag, L, mid, p, w);
    else rs = insert(x->rs, tag * x->tag, mid + 1, R, p, w);
    return push_up(x, ls, rs);
}
auto query(const NodeRc &x, int L, int R, int l, int r) -> mint {
    if (!x) return mint{};
    if (l <= L && R <= r) {
        return x->sum;
    }
    const int mid = L + (R - L) / 2;
    mint sum = 0;
    if (l <= mid) sum += query(x->ls, L, mid, l, r);
    if (r > mid) sum += query(x->rs, mid + 1, R, l, r);
    return sum * x->tag;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const_cast<mint &>(NodeRc {} -> tag) = 1;

    int n, k;
    std::cin >> n >> k;

    std::vector<std::pair<int, int>> p(n);
    for (auto &[l, r] : p) std::cin >> l >> r;
    std::ranges::sort(p);

    const int min_p = 0;
    const int max_p = n * 2 + 1;

    std::vector<std::vector<mint>> S2(k + 1);
    S2[0] = std::vector<mint>{mint{1}};
    for (int i = 1; i <= k; ++i) {
        S2[i].resize(i + 1);
        for (int j = 0; j <= i; ++j) {
            S2[i][j] = (j - 1 >= 0 ? S2[i - 1][j - 1] : 0) +
                       (j <= i - 1 ? S2[i - 1][j] * j : 0);
        }
    }
    std::vector<mint> fact(k + 1);
    fact[0] = 1;
    for (int i = 1; i <= k; ++i) fact[i] = fact[i - 1] * i;

    std::vector<NodeRc> rt(k + 1);
    rt[0] = insert(rt[0], mint{1}, min_p, max_p, min_p, 1);

    for (int idx = 0; idx < n; ++idx) {
        const auto [l, r] = p[idx];

        for (int i = 0; i <= k; ++i) {
            mint sum = query(rt[i], min_p, max_p, min_p, r);
            if (i - 1 >= 0) {
                sum += query(rt[i - 1], min_p, max_p, min_p, l - 1);
            }
            rt[i] = insert(rt[i], mint{1}, min_p, max_p, r, sum);
            rt[i] = multiply(rt[i], min_p, max_p, r + 1, max_p, 2);
        }
    }

    mint ans = 0;
    for (int i = 0; i <= k; ++i) {
        const mint sum = query(rt[i], min_p, max_p, min_p, max_p);
        ans += sum * S2[k][i] * fact[i];
    }
    std::cout << ans() << '\n';
}
