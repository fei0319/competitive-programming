#include <cstdio>

int n, k, x;

void solve() {
    scanf("%d%d%d", &n, &k, &x);
    if (x != 1) {
        puts("YES");
        printf("%d\n", n);
        for (int i = 1; i <= n; ++i)
            printf("1 ");
        puts("");
    } else if (k == 1) {
        puts("NO");
    } else if (k == 2) {
        if (n % 2 == 0) {
            puts("YES");
            printf("%d\n", n / 2);
            for (int i = 1; i <= n / 2; ++i)
                printf("2 ");
            puts("");
        } else {
            puts("NO");
        }
    } else {
        if (n % 2 == 0) {
            puts("YES");
            printf("%d\n", n / 2);
            for (int i = 1; i <= n / 2; ++i)
                printf("2 ");
            puts("");
        } else {
            puts("YES");
            printf("%d\n", n / 2);
            for (int i = 1; i < n / 2; ++i)
                printf("2 ");
            puts("3");
        }
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
}