#include <bits/stdc++.h>

template <typename T>
struct Median {
    std::multiset<T> l{};
    std::multiset<T> r{};
    void insert(const T &x) {
        if (l.empty()) r.insert(x);
        else if (r.empty()) l.insert(x);
        else {
            if (x >= *r.begin()) r.insert(x);
            else l.insert(x);
        }
        adjust();
    }
    void erase(const T &x) {
        if (const auto it = l.find(x); it != l.end()) {
            l.erase(it);
        } else if (const auto it = r.find(x); it != r.end()) {
            r.erase(it);
        }
        adjust();
    }
    void adjust() {
        while (l.size() >= r.size() + 2) {
            const auto it = --l.end();
            r.insert(std::move(*it));
            l.erase(it);
        }
        while (l.size() < r.size()) {
            const auto it = r.begin();
            l.insert(std::move(*it));
            r.erase(it);
        }
    }
    std::pair<T, T> get() const {
        if (l.size() > r.size()) {
            const T x = *--l.end();
            return std::make_pair(x, x);
        }
        return std::make_pair(*--l.end(), *r.begin());
    }
};

void solve() {
    namespace ranges = std::ranges;

    int n, k;
    std::cin >> n >> k;

    std::vector<int> a(n);
    for (int &i : a) {
        std::cin >> i;
    }

    std::vector<int> vals{a};
    ranges::sort(vals);

    std::unordered_map<int, int> occ{};
    std::vector<int> idx(n);
    for (int i : std::views::iota(0, n)) {
        idx[i] =
            ranges::lower_bound(vals, a[i]) - vals.begin() + occ[a[i]]++;
    }

    auto check = [&](int x) -> std::optional<std::pair<int, int>> {
        std::vector<int> b(n);
        ranges::transform(idx, b.begin(), [x](int v) {
            if (v * 2 == x) return 0;
            return v * 2 > x ? 1 : -1;
        });

        std::vector<int> s(n);
        std::inclusive_scan(b.begin(), b.end(), s.begin());

        std::unordered_map<int, int> S{{0, -1}};
        for (int i = k - 1; i < n; ++i, S.try_emplace(s[i - k], i - k)) {
            if (const auto it = S.find(s[i]); it != S.end()) {
                return std::make_pair(it->second + 1, i);
            }
        }

        return std::nullopt;
    };

    assert(check(n - 1).has_value());

    const int v_min =
        *ranges::lower_bound(std::views::iota(0, n), true, {},
                             [&](int x) { return check(x).has_value(); });
    const int v_max = *ranges::lower_bound(
        std::views::iota(n - 1, n * 2) | std::views::reverse, true, {},
        [&](int x) { return check(x).has_value(); });

    auto [l, r] = check(v_min).value();
    const auto [L, R] = check(v_max).value();
    Median<int> t{};
    for (int i = l; i <= r; ++i) t.insert(a[i]);

    std::unordered_map<int, std::pair<int, int>> ans{};
    auto update_ans = [&]() {
        const auto [min, max] = t.get();
        int cnt = 0;
        auto apply = [&](auto &&view) {
            for (int i : view) {
                const auto [_, ok] =
                    ans.try_emplace(i, std::make_pair(l, r));
                if (!ok) return;
            }
        };
        apply(std::views::iota(min, max + 1));
        apply(std::views::iota(min, max + 1) | std::views::reverse);
    };
    update_ans();

    while (l > L) {
        t.insert(a[--l]);
        update_ans();
    }
    while (r < R) {
        t.insert(a[++r]);
        update_ans();
    }
    while (l < L) {
        t.erase(a[l++]);
        update_ans();
    }
    while (r > R) {
        t.erase(a[r--]);
        update_ans();
    }

    std::cout << ans.size() << '\n';
    for (const auto &[v, p] : ans) {
        std::cout << std::format("{} {} {}\n", v, p.first + 1,
                                 p.second + 1);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }
}
