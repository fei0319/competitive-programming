#include <bits/stdc++.h>

using i64 = int64_t;
struct Line {
    int k, b, id;
};

void solve() {
    int n;
    std::cin >> n;

    std::vector<Line> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i].k >> a[i].b;
        a[i].id = i;
    }

    auto check = [](const Line &x1, const Line &x2, const Line &x3) {
        const auto [k1, b1, _1] = x1;
        const auto [k2, b2, _2] = x2;
        const auto [k3, b3, _3] = x3;
        return i64(b3 - b1) * (k1 - k2) <= i64(b2 - b1) * (k1 - k3);
    };

    std::ranges::sort(
        a, [](const Line &x1, const Line &x2) { return x1.k < x2.k; });
    std::vector<Line> t{};
    for (const Line &x : a) {
        while (!t.empty() && t.back().k == x.k && t.back().b <= x.b)
            t.pop_back();
        if (!t.empty() && t.back().k == x.k) continue;
        while (t.size() >= 2 && check(t[t.size() - 2], t.back(), x))
            t.pop_back();
        t.push_back(x);
    }

    std::vector<int> ans{};
    std::ranges::transform(t, std::back_inserter(ans),
                           [](const auto &x) { return x.id + 1; });
    std::ranges::sort(ans);
    std::copy(ans.begin(), ans.end(),
              std::ostream_iterator<int>(std::cout, " "));
}

int main() { solve(); }
