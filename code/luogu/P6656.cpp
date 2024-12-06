#include <bits/stdc++.h>

using u64 = uint64_t;

constexpr u64 B = 319;
constexpr int MAXN = 1e6 + 19;
u64 BP[MAXN];
void init() {
    BP[0] = 1;
    for (int i = 1; i < MAXN; ++i) BP[i] = BP[i - 1] * B;
}

struct Hash {
    int len;
    u64 v;
    friend Hash operator+(const Hash &lhs, const Hash &rhs) {
        int nlen = lhs.len + rhs.len;
        u64 nv = lhs.v * BP[rhs.len] + rhs.v;
        return Hash{nlen, nv};
    }
    friend Hash operator%(const Hash &lhs, const Hash &rhs) {
        int nlen = lhs.len - rhs.len;
        u64 nv = lhs.v - rhs.v * BP[nlen];
        return Hash{nlen, nv};
    }
    friend bool operator==(const Hash &lhs, const Hash &rhs) {
        return lhs.len == rhs.len && lhs.v == rhs.v;
    }

    static Hash from_char(char c) { return Hash{1, (u64)c}; }
};

int main() {
    init();
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;
    const int n = s.size();

    std::vector<Hash> h(n);
    for (int i = 0; i < n; ++i) {
        h[i] = Hash::from_char(s[i]);
        if (i - 1 >= 0) h[i] = h[i - 1] + h[i];
    }
    auto query = [&](int l, int r) -> Hash {
        if (l == 0) return h[r];
        else return h[r] % h[l - 1];
    };

    auto lyndon_roots = [&](auto &op) -> std::vector<std::pair<int, int>> {
        auto cmp = [&](int x, int y) -> bool {
            // Whether x-suffix < y-suffix
            int l = 0, r = std::min(n - y, n - x);
            while (l < r) {
                int mid = (l + r + 1) / 2;
                if (query(x, x + mid - 1) == query(y, y + mid - 1))
                    l = mid;
                else r = mid - 1;
            }
            return op(x + l, y + l);
        };
        std::vector<int> stk;
        std::vector<std::pair<int, int>> res;
        for (int i = 0; i <= n; ++i) {
            while (!stk.empty() && cmp(i, stk.back())) {
                res.emplace_back(stk.back(), i - 1);
                stk.pop_back();
            }
            stk.push_back(i);
        }
        return res;
    };

    auto op1 = [&](int x, int y) {
        int vx = x >= n ? -1e9 : s[x];
        int vy = y >= n ? -1e9 : s[y];
        return vx < vy;
    };
    auto op2 = [&](int x, int y) {
        int vx = x >= n ? -1e9 : 1000 - s[x];
        int vy = y >= n ? -1e9 : 1000 - s[y];
        return vx < vy;
    };
    auto roots = lyndon_roots(op1), tmp = lyndon_roots(op2);
    roots.insert(roots.end(), tmp.begin(), tmp.end());

    std::vector<std::pair<std::pair<int, int>, int>> runs;
    for (auto [i, j] : roots) {
        int p = j - i + 1;
        int l, r;

        l = 0, r = i;
        while (l < r) {
            int mid = (l + r) / 2;
            if (query(mid, j - p) == query(mid + p, j)) r = mid;
            else l = mid + 1;
        }
        i = l;

        l = j, r = n - 1;
        while (l < r) {
            int mid = (l + r + 1) / 2;
            if (query(i + p, mid) == query(i, mid - p)) l = mid;
            else r = mid - 1;
        }
        j = l;

        if (j - i + 1 >= p * 2) runs.emplace_back(std::make_pair(i, j), p);
    }

    std::sort(runs.begin(), runs.end());
    runs.resize(std::unique(runs.begin(), runs.end()) - runs.begin());

    std::cout << runs.size() << '\n';
    for (auto [v, p] : runs) {
        auto [i, j] = v;
        std::cout << i + 1 << ' ' << j + 1 << ' ' << p << '\n';
    }
}
