#include <algorithm>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

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
        if (idx) pool[idx].ref += 1;
    }
    Rc(Rc &&other) {
        idx = other.idx;
        if (idx) other.idx = 0;
    }
    ~Rc() { release(idx); }
    Rc &operator=(const Rc &other) {
        if (this != &other) {
            release(idx);
            idx = other.idx;
            if (idx) pool[idx].ref += 1;
        }
        return *this;
    }
    Rc &operator=(Rc &&other) {
        if (this != &other) {
            release(idx);
            idx = other.idx;
            if (idx) other.idx = 0;
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

struct SuffixArray {
    int n;
    std::vector<int> sa, rk, lc;
    explicit SuffixArray(const auto &s) {
        n = s.size();
        sa.resize(n);
        lc.resize(n - 1);
        rk.resize(n);
        std::iota(sa.begin(), sa.end(), 0);
        std::sort(sa.begin(), sa.end(),
                  [&](int a, int b) { return s[a] < s[b]; });
        rk[sa[0]] = 0;
        for (int i = 1; i < n; ++i)
            rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
        int k = 1;
        std::vector<int> tmp, cnt(n);
        tmp.reserve(n);
        while (rk[sa[n - 1]] < n - 1) {
            tmp.clear();
            for (int i = 0; i < k; ++i) tmp.push_back(n - k + i);
            for (auto i : sa)
                if (i >= k) tmp.push_back(i - k);
            std::fill(cnt.begin(), cnt.end(), 0);
            for (int i = 0; i < n; ++i) ++cnt[rk[i]];
            for (int i = 1; i < n; ++i) cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; --i)
                sa[--cnt[rk[tmp[i]]]] = tmp[i];
            std::swap(rk, tmp);
            rk[sa[0]] = 0;
            for (int i = 1; i < n; ++i)
                rk[sa[i]] =
                    rk[sa[i - 1]] + (tmp[sa[i - 1]] < tmp[sa[i]] ||
                                     sa[i - 1] + k == n ||
                                     tmp[sa[i - 1] + k] < tmp[sa[i] + k]);
            k *= 2;
        }
        for (int i = 0, j = 0; i < n; ++i) {
            if (rk[i] == 0) {
                j = 0;
            } else {
                for (j -= j > 0; i + j < n && sa[rk[i] - 1] + j < n &&
                                 s[i + j] == s[sa[rk[i] - 1] + j];)
                    ++j;
                lc[rk[i] - 1] = j;
            }
        }
    }
};

struct RMQ {
    std::vector<std::vector<int>> f;
    explicit RMQ(const std::vector<int> &a) {
        const size_t n = a.size();

        f.resize(32 - __builtin_clz(n));
        f[0] = a;
        for (int b = 1; b < f.size(); ++b) {
            f[b].resize(n);
            for (int i = 0; i + (1 << (b - 1)) < n; ++i) {
                f[b][i] =
                    std::min(f[b - 1][i], f[b - 1][i + (1 << (b - 1))]);
            }
        }
    }
    int query(int l, int r) {
        const int b = 31 - __builtin_clz(r - l + 1);
        return std::min(f[b][l], f[b][r - (1 << b) + 1]);
    }
};

constexpr int MAXS = 1e7;
struct Node {
    Rc<const Node, MAXS, 12> ls, rs;
    int cnt;
};
using NodeRc = Rc<const Node, MAXS, 12>;

NodeRc push_up(const NodeRc &ls, const NodeRc &rs) {
    return NodeRc::make(ls, rs, ls->cnt + rs->cnt);
}
NodeRc insert(const NodeRc &x, int L, int R, int v) {
    if (L == R) return NodeRc::make(NodeRc{}, NodeRc{}, x->cnt + 1);
    const int mid = L + (R - L) / 2;
    if (v <= mid) return push_up(insert(x->ls, L, mid, v), x->rs);
    else return push_up(x->ls, insert(x->rs, mid + 1, R, v));
}
int query(const NodeRc &x, int L, int R, int l, int r) {
    if (!x) return 0;
    if (l <= L && R <= r) return x->cnt;
    const int mid = L + (R - L) / 2;
    int res = 0;
    if (l <= mid) res += query(x->ls, L, mid, l, r);
    if (r > mid) res += query(x->rs, mid + 1, R, l, r);
    return res;
}

void solve() {
    int n, q;
    std::cin >> n >> q;

    std::string s;
    std::cin >> s;

    struct Query {
        int a, b, c, d;
    };
    std::vector<Query> Q(q);
    for (auto &[a, b, c, d] : Q) {
        std::cin >> a >> b >> c >> d;
        --a, --b, --c, --d;
    }

    auto sa_ctx = SuffixArray{s};
    auto h_rmq = RMQ{sa_ctx.lc};

    std::vector<NodeRc> rt(n + 1);
    for (int i = n - 1; i >= 0; --i) {
        rt[i] = insert(rt[i + 1], 0, n - 1, sa_ctx.rk[i]);
    }

    for (const auto [a, b, c, d] : Q) {
        auto check = [&](int len) -> bool {
            if (len == 0) return true;
            const NodeRc &x = rt[a];
            const NodeRc &y = rt[b - len + 2];

            const int m = sa_ctx.rk[c];
            const int l = *std::ranges::lower_bound(
                std::views::iota(0, m + 1), true, {}, [&](int x) {
                    return x == m || h_rmq.query(x, m - 1) >= len;
                });
            const int r = *std::ranges::lower_bound(
                std::views::iota(m, n) | std::views::reverse, true, {},
                [&](int x) {
                    return x == m || h_rmq.query(m, x - 1) >= len;
                });
            return query(x, 0, n - 1, l, r) > query(y, 0, n - 1, l, r);
        };

        const int max_len = std::min(d - c + 1, b - a + 1);
        const int res = *std::ranges::lower_bound(
            std::views::iota(0, max_len + 1) | std::views::reverse, true,
            {}, check);
        std::cout << res << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();
}