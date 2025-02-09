#include <bits/stdc++.h>

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

struct BIT {
    std::vector<int> tr;
    explicit BIT(int n) : tr(n) {}
    void update(int x, int k) {
        for (x += 1; x - 1 < tr.size(); x += x & -x) tr[x - 1] += k;
    }
    int query(int x) {
        int res = 0;
        for (x += 1; x; x -= x & -x) res += tr[x - 1];
        return res;
    }
};

using u64 = uint64_t;
constexpr int MAXN = 1e6 + 19;
constexpr u64 B = 20040319;
u64 BP[MAXN];
void init() {
    BP[0] = 1;
    for (int i = 1; i < MAXN; ++i) BP[i] = BP[i - 1] * B;
}
template <typename B>
struct Hash {
    int len;
    B v;
    friend Hash operator*(const Hash &lhs, const Hash &rhs) {
        int len = lhs.len + rhs.len;
        B v = lhs.v * BP[rhs.len] + rhs.v;
        return Hash{len, v};
    }
    friend Hash operator%(const Hash &lhs, const Hash &rhs) {
        int len = lhs.len - rhs.len;
        B v = lhs.v - rhs.v * BP[len];
        return Hash{len, v};
    }
    friend bool operator==(const Hash &lhs, const Hash &rhs) {
        return lhs.v == rhs.v && lhs.len == rhs.len;
    }
    static Hash from_char(char c) { return Hash{1, B(c) + 19ULL}; }
};

struct Query {
    int i, r;
};

using Run = std::array<int, 3>;
std::vector<Run> all_runs(const std::string &s) {
    const int n = s.size();
    std::vector<int> s0(n), s1(n);
    for (int i = 0; i < n; ++i) {
        s0[i] = s[i];
        s1[i] = 1000 - s[i];
    }
    std::vector<int> rk0{SuffixArray{s0}.rk}, rk1{SuffixArray{s1}.rk};

    std::vector<Hash<u64>> h(n);
    for (int i = 0; i < n; ++i) {
        h[i] = Hash<u64>::from_char(s[i]);
        if (i) h[i] = h[i - 1] * h[i];
    }
    auto query = [&](int l, int r) {
        if (l == 0) return h[r];
        return h[r] % h[l - 1];
    };

    std::vector<Run> res;
    auto lyndon_roots = [&](const std::vector<int> &rk) {
        std::vector<int> stk;
        std::vector<std::pair<int, int>> root;
        for (int i = 0; i < n; ++i) {
            while (!stk.empty() && rk[stk.back()] > rk[i]) {
                root.emplace_back(stk.back(), i - 1);
                stk.pop_back();
            }
            stk.push_back(i);
        }
        while (!stk.empty()) {
            root.emplace_back(stk.back(), n - 1);
            stk.pop_back();
        }

        for (auto [L, R] : root) {
            // std::cout << "Root: " << L << ' ' << R << '\n';
            int p = R - L + 1;
            int l, r;

            l = 0, r = L;
            while (l < r) {
                int mid = (l + r) / 2;
                if (query(mid, R - p) == query(mid + p, R)) r = mid;
                else
                    l = mid + 1;
            }
            L = l;

            l = R, r = n - 1;
            while (l < r) {
                int mid = (l + r + 1) / 2;
                if (query(L + p, mid) == query(L, mid - p)) l = mid;
                else
                    r = mid - 1;
            }
            R = l;

            // std::cout << "extended to " << L << ' ' << R << '\n';

            if (R - L + 1 >= p * 2) res.push_back(Run{L, R, p});
        }
    };
    lyndon_roots(rk0);
    lyndon_roots(rk1);

    std::sort(res.begin(), res.end());
    res.resize(std::unique(res.begin(), res.end()) - res.begin());
    return res;
}

int main() {
    init();

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int _;
    std::cin >> _;

    int n, q;
    std::cin >> n >> q;
    std::string s;
    std::cin >> s;
    std::vector<Query> Q(q);
    for (int i = 0; i < q; ++i) {
        std::cin >> Q[i].i >> Q[i].r;
        --Q[i].i;
    }

    std::vector<int> ans(q);

    {
        auto rk = SuffixArray{s}.rk;
        // rk[i] < rk[i + l] && l <= r
        struct Op1 {
            int id, rk, k;
        };
        std::vector<std::vector<Op1>> op1(n);
        for (int id = 0; id < q; ++id) {
            auto [i, r] = Q[id];

            op1[i].push_back(Op1{id, rk[i], 1});
            if (i + r + 1 < n) {
                op1[i + r + 1].push_back(Op1{id, rk[i], -1});
            }
        }

        BIT mt(n);
        for (int i = n - 1; i >= 0; --i) {
            mt.update(rk[i], 1);
            for (auto [id, rk, k] : op1[i]) {
                ans[id] += k * (mt.query(n - 1) - mt.query(rk));
            }
        }
    }

    std::vector<Run> run = all_runs(s);
    {
        std::vector<Run> nrun;
        for (auto [i, j, p] : run) {
            if (j + 1 < n && s[j + 1 - p] < s[j + 1]) {
                nrun.push_back(Run{i, j, p});
            }
        }
        run = nrun;
    }

    {
        std::vector<std::vector<int>> to_ins(n);
        for (auto [i, j, p] : run) {
            std::vector<int> v;
            for (int k = 1; j - 2 * k * p + 1 >= i; ++k) {
                v.push_back(k * p);
                to_ins[j - 2 * k * p + 1].push_back(k * p);
            }
            if (i - 1 >= 0)
                for (int v : v) {
                    to_ins[i - 1].push_back(-v);
                }
        }

        struct Op2 {
            int id, r;
        };
        std::vector<std::vector<Op2>> op2(n);
        for (int id = 0; id < q; ++id) {
            auto [i, r] = Q[id];
            op2[i].push_back(Op2{id, r});
        }

        BIT mt(n + 1);
        for (int i = n - 1; i >= 0; --i) {
            for (int v : to_ins[i]) {
                if (v > 0) mt.update(v, 1);
                else
                    mt.update(-v, -1);
            }
            for (auto [id, r] : op2[i]) {
                ans[id] -= mt.query(r);
            }
        }
    }

    std::copy(ans.begin(), ans.end(),
              std::ostream_iterator<int>(std::cout, "\n"));
}

/*
0
5 1
ababb
1 2
*/
