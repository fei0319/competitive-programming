#include <algorithm>
#include <cstdio>

constexpr int maxn = 1e5 + 19;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

int n, a[maxn];

int get_mind(int x, int d) {
    if (d == 0) return 0;
    while (x % d != 0 && d * d <= x) ++d;
    if (x % d == 0) return d;
    else return 0;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);

    std::sort(a + 1, a + 1 + n);
    int g = a[1], ans = 1, mind = get_mind(a[1], 2);
    ans = std::max(ans, a[1] / 2);
    for (int i = 1; i <= n; ++i) {
        g = gcd(g, a[i]);
        mind = get_mind(g, mind);
        if (2 * g <= a[i + 1] || i == n) {
            ans = std::max(ans, g);
        }
        if (mind) {
            ans = std::max(ans, g / mind);
        }
    }
    printf("%d\n", ans);
}
