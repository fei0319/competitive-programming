#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <numeric>
#include <random>
#include <ranges>
#include <unordered_set>
#include <vector>

using i64 = int64_t;

struct Frac {
    int p, q;
    Frac(int x, int y) {
        int g = std::gcd(x, y);
        p = x / g;
        q = y / g;
    }
    auto operator<=>(const Frac &other) const {
        return (i64)p * other.q <=> (i64)other.p * q;
    }
    bool operator==(const Frac &other) const {
        return (*this <=> other) == 0;
    }
};

struct Node {
    int x, y, w;
};

namespace S {
    constexpr size_t MAXS = 1e5;
    i64 lv[MAXS], rv[MAXS], sum[MAXS], res[MAXS];
    void pull_up(int x) {
        lv[x] = std::max(lv[x << 1], lv[x << 1 | 1] + sum[x << 1]);
        rv[x] = std::max(rv[x << 1 | 1], rv[x << 1] + sum[x << 1 | 1]);
        sum[x] = sum[x << 1] + sum[x << 1 | 1];
        res[x] = std::max(
            {res[x << 1], res[x << 1 | 1], rv[x << 1] + lv[x << 1 | 1]});
    }
    void modify(int x, int L, int R, int p, int w) {
        if (L == R) {
            lv[x] = rv[x] = res[x] = std::max(0, w);
            sum[x] = w;
            return;
        }
        int mid = L + (R - L) / 2;
        if (p <= mid) modify(x << 1, L, mid, p, w);
        else modify(x << 1 | 1, mid + 1, R, p, w);
        pull_up(x);
    }
}; // namespace S

void solve() {
    int n;
    std::cin >> n;

    std::map<std::pair<int, int>, i64> W;
    for (int _ : std::views::iota(0, n)) {
        int x, y, w;
        std::cin >> x >> y >> w;
        W[{x, y}] += w;
    }

    std::vector<Node> a;
    for (auto [p, w] : W) {
        auto [x, y] = p;
        a.emplace_back(x, y, w);
    }
    n = a.size();

    std::vector<std::pair<Frac, int>> d;
    d.emplace_back(Frac{-1, 0}, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i].x > a[j].x) {
                auto k = Frac{a[j].y - a[i].y, a[i].x - a[j].x};
                d.emplace_back(k, i * n + j);
            }
        }
    }
    std::ranges::sort(d);

    std::vector<int> idx(n), rnk(n);
    std::iota(idx.begin(), idx.end(), 0);
    std::ranges::sort(idx, [&](int i1, int i2) -> bool {
        return a[i1].x != a[i2].x ? a[i1].x > a[i2].x : a[i1].y < a[i2].y;
    });
    for (int i = 0; i < n; ++i) {
        S::modify(1, 0, n - 1, i, a[idx[i]].w);
        rnk[idx[i]] = i;
    }
    i64 ans = S::res[1];

    auto pull = [&](int i) {
        int j = idx[rnk[i] + 1];
        S::modify(1, 0, n - 1, rnk[i], a[j].w);
        S::modify(1, 0, n - 1, rnk[j], a[i].w);
        std::swap(idx[rnk[i]], idx[rnk[j]]);
        std::swap(rnk[i], rnk[j]);
    };

    for (int l = 0, r; l < d.size(); l = r + 1) {
        r = l;
        std::unordered_set<int> uset{d[r].second};
        while (r + 1 < d.size() && d[r + 1].first == d[r].first) {
            uset.insert(d[++r].second);
        }

        std::vector<int> vec;
        for (int x : uset) vec.push_back(x / n);
        std::ranges::sort(
            vec, [&](int i1, int i2) { return rnk[i1] > rnk[i2]; });
        vec.resize(std::unique(vec.begin(), vec.end()) - vec.begin());
        for (int i : vec) {
            while (rnk[i] + 1 < n &&
                   uset.contains(i * n + idx[rnk[i] + 1])) {
                pull(i);
            }
        }

        ans = std::max(ans, S::res[1]);
    }

    std::cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();
}