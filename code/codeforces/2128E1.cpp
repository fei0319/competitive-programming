#include <bits/stdc++.h>

template <typename T>
struct Median {
    std::multiset<T> l{};
    std::multiset<T> r{};
    void insert(const T &x) {
        if (l.empty()) r.insert(x);
        else if (r.empty())
            l.insert(x);
        else {
            if (x >= *r.begin()) r.insert(x);
            else
                l.insert(x);
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
};

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> a(n);
    for (int &i : a) {
        std::cin >> i;
    }

    std::vector<int> vals{a};
    std::ranges::sort(vals);

    std::unordered_map<int, int> occ{};
    for (int &i : a) {
        i = std::ranges::lower_bound(vals, i) - vals.begin() + occ[i]++;
    }

    auto check = [&](int x) -> std::optional<std::pair<int, int>> {
        std::vector<int> b(n);
        std::transform(a.begin(), a.end(), b.begin(), [x](int v) {
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

    const int median = [&]() {
        std::vector<int> tmp{a};
        std::nth_element(tmp.begin(), tmp.begin() + tmp.size() / 2,
                         tmp.end());
        return tmp[tmp.size() / 2];
    }();

    assert(check(median * 2) || check(median * 2 - 1));

    const int v = *std::ranges::lower_bound(
        std::ranges::iota_view{median, static_cast<int>(n)} |
            std::views::reverse,
        true, {}, [&](int x) { return check(x * 2) || check(x * 2 - 1); });

    const auto opt = check(v * 2) ? check(v * 2) : check(v * 2 - 1);
    const auto &[l, r] = opt.value();

    std::cout << std::format("{} {} {}\n", vals[v], l + 1, r + 1);
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
