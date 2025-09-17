#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <vector>

using fp = long double;

template <typename T>
struct Point {
    T x, y;
    auto operator<=>(const Point &) const = default;
};
template <typename T, typename U>
auto operator+(const Point<T> &p1, const Point<U> &p2) {
    return Point{p1.x + p2.x, p1.y + p2.y};
}
template <typename T, typename U>
auto operator-(const Point<T> &p1, const Point<U> &p2) {
    return Point{p1.x - p2.x, p1.y - p2.y};
}
template <typename T>
T cross(auto p1, auto p2) {
    return (T)p1.x * p2.y - (T)p2.x * p1.y;
}
auto arc(auto p) { return std::atan2l(p.y, p.x); }
auto intersection(Point<fp> a, Point<fp> b, Point<fp> p, Point<fp> q) {
    Point<fp> r{b.x - a.x, b.y - a.y};
    Point<fp> s{q.x - p.x, q.y - p.y};
    const fp t = cross<fp>(p - a, s) / cross<fp>(r, s);
    return Point{a.x + r.x * t, a.y + r.y * t};
}

template <typename T>
struct Line {
    Point<T> u, v;
};

template <typename P>
auto make_hull(std::vector<P> p) {
    std::ranges::sort(p);
    std::vector<P> hi, lo;
    for (const auto p : p) {
        while (hi.size() >= 2 &&
               cross<fp>(hi[hi.size() - 1] - hi[hi.size() - 2],
                         p - hi[hi.size() - 2]) >= 0)
            hi.pop_back();
        if (!hi.empty() && hi.back().x == p.x) hi.pop_back();
        hi.push_back(p);
        while (lo.size() >= 2 &&
               cross<fp>(lo[lo.size() - 1] - lo[lo.size() - 2],
                         p - lo[lo.size() - 2]) <= 0)
            lo.pop_back();
        if (lo.empty() || lo.back().x != p.x) lo.push_back(p);
    }

    return std::make_pair(hi, lo);
}

fp dist(Point<fp> a, Point<fp> b, Point<fp> p) {
    const fp area = cross<fp>(a, b) + cross<fp>(b, p) + cross<fp>(p, a);
    const fp bottom = std::hypot(a.x - b.x, a.y - b.y);
    return area / bottom;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<Point<fp>> a(n);
    for (auto &[x, y] : a) std::cin >> x >> y;

    auto [hi, lo] = make_hull(a);
    std::vector<Point<fp>> h(lo);
    for (const auto p : hi | std::views::reverse) {
        if (p != h.front() && p != h.back()) {
            h.push_back(p);
        }
    }

    fp ans = std::numeric_limits<fp>::max();
    std::vector<Point<fp>> mat{};

    int l = 0, r = 0, d = 0;
    for (int i = 0; i < h.size(); ++i) {
        auto horizontal = h[(i + 1) % h.size()] - h[i];
        while (cross<fp>(horizontal, h[(d + 1) % h.size()] - h[d]) >= 0)
            d = (d + 1) % h.size();

        auto vertical = Point<fp>(horizontal.y, -horizontal.x);
        while (cross<fp>(vertical, h[(l + 1) % h.size()] - h[l]) >= 0)
            l = (l + 1) % h.size();
        while (cross<fp>(vertical,
                         h[(l + h.size() - 1) % h.size()] - h[l]) >= 0)
            l = (l + h.size() - 1) % h.size();
        while (cross<fp>(vertical, h[(r + 1) % h.size()] - h[r]) <= 0)
            r = (r + 1) % h.size();
        while (cross<fp>(vertical,
                         h[(r + h.size() - 1) % h.size()] - h[r]) <= 0)
            r = (r + h.size() - 1) % h.size();

        const fp H = dist(h[i], h[(i + 1) % h.size()], h[d]);
        const fp W = dist(Point<fp>{0, 0}, vertical, h[l]) -
                     dist(Point<fp>{0, 0}, vertical, h[r]);

        if (const fp cur_ans = std::abs(H * W); cur_ans < ans) {
            ans = cur_ans;

            auto get_point = [&](auto a, auto b, auto p) {
                auto q = p + Point<fp>{b.y - a.y, a.x - b.x};
                auto x = intersection(a, b, p, q);
                mat.push_back(intersection(a, b, p, q));
            };

            mat.clear();
            get_point(h[i], h[(i + 1) % h.size()], h[l]);
            get_point(h[d], h[d] + h[(i + 1) % h.size()] - h[i], h[l]);
            get_point(h[d], h[d] + h[(i + 1) % h.size()] - h[i], h[r]);
            get_point(h[i], h[(i + 1) % h.size()], h[r]);
        }
    }

    std::cout << std::fixed << std::setprecision(12);
    std::cout << ans << '\n';
    for (const auto [x, y] : mat) {
        std::cout << x << ' ' << y << '\n';
    }
}
