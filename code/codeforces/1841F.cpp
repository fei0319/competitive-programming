#include <bits/stdc++.h>

using ld = __int128;
using ll = long long int;

const int MAXN = 3e5 + 19;

template <typename T>
void write(const T &x) {
    if (x >= 10) {
        write(x / 10);
    }
    std::cout << char(x % 10 + '0');
}

struct Point {
    ll x, y;
    friend ll operator*(const Point &a, const Point &b) {
        return (ll)a.x * b.y - (ll)a.y * b.x;
    }
    friend Point operator-(const Point &a, const Point &b) {
        return Point{a.x - b.x, a.y - b.y};
    }
    friend Point operator+(const Point &a, const Point &b) {
        return Point{a.x + b.x, a.y + b.y};
    }
    int type() const { return y < 0 || (y == 0 && x < 0); }
} p[MAXN * 2];

int n;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;

    int t = 0;
    for (int i = 1; i <= n; ++i) {
        int a, b, c, d;
        std::cin >> a >> b >> c >> d;
        if (a != b || c != d) {
            p[++t] = Point{a - b, c - d};
        }
    }
    n = t;

    std::sort(p + 1, p + 1 + n, [](const Point &a, const Point &b) {
        if (a.type() == b.type()) {
            return a * b > 0;
        }
        return a.type() < b.type();
    });
    t = 0;
    for (int i = 1; i <= n; ++i) {
        if (t && p[i] * p[t] == 0 &&
            (ld)p[i].x * p[t].x + (ld)p[i].y * p[t].y > 0) {
            p[t] = p[t] + p[i];
        } else {
            p[++t] = p[i];
        }
    }
    n = t;

    std::copy(p + 1, p + 1 + n, p + 1 + n);

    ld ans = 0;
    int l = 1;
    Point sum{0, 0};
    for (int i = 1; i <= n + n; ++i) {
        while (i - l + 1 > n || p[i] * p[l] > 0 ||
               (p[i] * p[l] == 0 &&
                (ll)p[i].x * p[l].x + (ll)p[i].y * p[l].y < 0)) {
            sum = sum - p[l++];
            ans = std::max(ans, (ld)sum.x * sum.x + (ld)sum.y * sum.y);
        }

        sum = sum + p[i];
        ans = std::max(ans, (ld)sum.x * sum.x + (ld)sum.y * sum.y);
    }

    write(ans);

    return 0;
}