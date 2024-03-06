#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using ll = long long int;
using ld = long double;

const ld B = 1e-8, T = 1e3;

int n, m;

ld query(const std::vector<std::pair<ld, ld>> &p, int d) {
    std::cout << "? " << p.size() << '\n';
    for (auto [x, y] : p) {
        if (d) {
            std::swap(x, y);
        }
        std::cout << x << ' ' << y << '\n';
    }
    std::cout << std::endl;

    ld res;
    std::cin >> res;
    return res;
}

ld get(int d) {
    std::vector<std::pair<ld, ld>> a;
    // position, length

    for (int i = 1; i <= 103; ++i) {
        a.emplace_back(i, B * i);
    }
    // if area == B * i, then
    // i + B * i - 1 <= x <= i + B * i

    std::vector<std::pair<ld, ld>> p;
    for (auto [pos, len] : a) {
        p.emplace_back(pos, T);
        p.emplace_back(pos, -T);
        p.emplace_back(pos + len, -T);
        p.emplace_back(pos + len, T);
    }
    p.emplace_back(0, T + 1);

    ld x = query(p, d);

    int t = -1;
    for (int i = 1; i <= 100; ++i) {
        if (fabsl(B * i - x) < 1e-9) {
            t = i;
            break;
        }
    }

    if (t == -1) {
        return 0;
    }

    ld r = t + B * t;
    return r - 1 + query({{r, T}, {r, -T}, {T, -T}, {T, T}}, d);
}

int main() {
    std::cin >> n >> m;
    std::cout << std::fixed << std::setprecision(14);

    ld x = get(0), y = get(1);
    std::cout << "! " << x << ' ' << y << std::endl;

    return 0;
}