#include <algorithm>
#include <cstdio>


constexpr int MAXN = 1e5 + 19;

int n, a[MAXN];

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            scanf("%d", a + i);
        std::sort(a + 1, a + 1 + n);
        int sz = n / 2;
        int ans = 0;
        for (int i = 1; i <= sz; ++i)
            ans -= a[i];
        for (int i = n; i > n - sz; --i)
            ans += a[i];
        printf("%d\n", ans);
    }
}