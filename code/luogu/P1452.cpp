#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <queue>
#include <random>
#include <ranges>

template <typename T>
struct Point {
    T x, y;
    auto operator<=>(const Point &) const = default;
};
template <typename T, typename U>
auto operator+(Point<T> p1, Point<U> p2) {
    return Point{p1.x + p2.x, p1.y + p2.y};
}
template <typename T, typename U>
auto operator-(Point<T> p1, Point<U> p2) {
    return Point{p1.x - p2.x, p1.y - p2.y};
}

template <typename T>
T cross(auto p1, auto p2) {
    return (T)p1.x * p2.y - (T)p2.x * p1.y;
}
using i64 = int64_t;

template <typename P>
auto make_hull(std::vector<P> p) {
    std::ranges::sort(p);

    std::vector<P> hi, lo;
    for (auto p : p) {
        while (hi.size() > 1 && cross<i64>(hi.back() - hi[hi.size() - 2],
                                           p - hi.back()) >= 0)
            hi.pop_back();
        while (!hi.empty() && hi.back().x == p.x) hi.pop_back();
        hi.push_back(p);
        while (lo.size() > 1 && cross<i64>(lo.back() - lo[lo.size() - 2],
                                           p - lo.back()) <= 0)
            lo.pop_back();
        if (lo.empty() || lo.back().x < p.x) lo.push_back(p);
    }
    return std::make_pair(hi, lo);
}

void solve() {
    int n;
    std::cin >> n;

    std::vector<Point<int>> a(n);
    for (auto &[x, y] : a) {
        std::cin >> x >> y;
    }

    const auto [hi, lo] = make_hull(a);
    std::vector<Point<int>> h = lo;
    for (const auto p : hi | std::views::reverse) {
        if (p != h.front() && p != h.back()) {
            h.push_back(p);
        }
    }

    i64 ans{};

    auto dist = [](auto p1, auto p2) {
        const i64 dx = p1.x - p2.x;
        const i64 dy = p1.y - p2.y;
        return dx * dx + dy * dy;
    };

    for (int i = 0, j = 0; i < h.size(); ++i) {
        while (i == j || cross<i64>(h[(i + 1) % h.size()] - h[i],
                                    h[(j + 1) % h.size()] - h[j]) > 0) {
            j = (j + 1) % h.size();
        }
        ans = std::max(
            {ans, dist(h[i], h[j]), dist(h[(i + 1) % h.size()], h[j]),
             dist(h[i], h[(j + 1) % h.size()]),
             dist(h[(i + 1) % h.size()], h[(j + 1) % h.size()])});
    }
    std::cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();
}
