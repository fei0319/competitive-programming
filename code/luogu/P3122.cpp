#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <type_traits>
#include <vector>

template <typename T>
struct Point {
    T x, y;
    auto operator<=>(const Point &) const = default;
};
template <typename T, typename U>
Point<std::common_type_t<T, U>> operator+(Point<T> p1, Point<U> p2) {
    return {p1.x + p2.x, p1.y + p2.y};
}
template <typename T, typename U>
Point<std::common_type_t<T, U>> operator-(Point<T> p1, Point<U> p2) {
    return {p1.x - p2.x, p1.y - p2.y};
}
template <typename T>
struct Line {
    Point<T> a, b;
    auto operator<=>(const Line &) const = default;
};
template <typename T>
T dot(auto p1, auto p2) {
    return (T)p1.x * p2.y - (T)p2.x * p1.y;
}
auto arg(auto p) { return std::atan2l(p.y, p.x); }

using fp = long double;
using i64 = int64_t;
struct Convex {
    std::set<std::pair<fp, Point<int>>> h{};
    std::set<std::pair<fp, Line<int>>> t{};
    Point<fp> m{};

    using Iter = decltype(h)::iterator;
    using IterT = decltype(t)::iterator;
    Iter prev(Iter it) const {
        if (it == h.begin()) it = h.end();
        return --it;
    }
    IterT prev(IterT it) const {
        if (it == t.begin()) it = t.end();
        return --it;
    }
    Iter next(Iter it) const {
        if (++it == h.end()) it = h.begin();
        return it;
    }
    IterT next(IterT it) const {
        if (++it == t.end()) it = t.begin();
        return it;
    }

    auto make_line(Iter it1, Iter it2) {
        const auto &p1 = it1->second;
        const auto &p2 = it2->second;
        return std::make_pair(arg(p2 - p1), Line<int>(p1, p2));
    }
    void add(Iter it) {
        t.erase(make_line(prev(it), next(it)));
        t.insert(make_line(prev(it), it));
        t.insert(make_line(it, next(it)));
    }
    void del(Iter it) {
        t.insert(make_line(prev(it), next(it)));
        t.erase(make_line(prev(it), it));
        t.erase(make_line(it, next(it)));
    }

    void init() {
        m = {};
        for (const auto [_, p] : h) {
            m = m + p;
        }
        m.x /= h.size();
        m.y /= h.size();

        decltype(h) new_h{};
        for (const auto [_, p] : h) {
            new_h.emplace(arg(p - m), p);
        }
        h = std::move(new_h);

        t.clear();
        for (auto it = h.begin(); it != h.end(); ++it) {
            t.insert(make_line(it, next(it)));
        }
    }

    void insert(Point<int> p) {
        if (h.size() <= 2) {
            h.emplace(0, p);
            if (h.size() == 3) init();
            return;
        }

        const auto [it, ok] = h.emplace(arg(p - m), p);
        if (!ok) return;

        if (dot<i64>(prev(it)->second - p, next(it)->second - p) >= 0) {
            h.erase(it);
            return;
        }

        add(it);
        while (h.size() > 3 && dot<i64>(next(it)->second - p,
                                        next(next(it))->second - p) <= 0) {
            del(next(it));
            h.erase(next(it));
        }
        while (h.size() > 3 && dot<i64>(prev(it)->second - p,
                                        prev(prev(it))->second - p) >= 0) {
            del(prev(it));
            h.erase(prev(it));
        }
    }

    bool check(int a, int b, i64 c) const {
        auto eval = [a, b, c](Point<int> p) {
            return (i64)a * p.x + (i64)b * p.y - c;
        };

        std::vector<Point<int>> check_list{};
        if (h.size() <= 8) {
            for (const auto [_, p] : h) check_list.push_back(p);
        } else {
            for (const fp theta :
                 {arg(Point<int>{b, -a}), arg(Point<int>{-b, a})}) {
                auto it = t.lower_bound({theta, {}});
                if (it == t.end()) it = t.begin();
                check_list.push_back(prev(it)->second.a);
                check_list.push_back(prev(it)->second.b);
                check_list.push_back(next(it)->second.a);
                check_list.push_back(next(it)->second.b);
            }
        }

        std::vector<i64> res{};
        for (const auto &p : check_list) {
            res.push_back(eval(p));
        }
        return std::ranges::max(res) < 0 || std::ranges::min(res) > 0;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    Convex h{};
    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        h.insert({x, y});
    }

    while (q--) {
        int op;
        std::cin >> op;
        if (op == 1) {
            int x, y;
            std::cin >> x >> y;
            h.insert({x, y});
        } else {
            int a, b;
            i64 c;
            std::cin >> a >> b >> c;
            const bool ans = h.check(a, b, c);
            std::cout << (ans ? "YES" : "NO") << '\n';
        }
    }
}
