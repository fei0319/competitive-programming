#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e6 + 19;

int n, win[maxn];
int s[maxn], ans[maxn];

int a[maxn];

int ask(int x) {
    std::cout << "? " << x << ' ';
    for (int i = 1; i <= n; ++i)
        if (i != x)
            std::cout << s[i];
        else
            std::cout << 0;
    std::cout << std::endl;

    std::cin >> x;
    return x;
}

void solve(void) {
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
        s[i] = 1, a[i] = i;
    for (int i = 1; i <= n; ++i) {
        s[i] = 0;
        win[i] = ask(i);
        s[i] = 1;
    }

    std::sort(a + 1, a + 1 + n, [](const int &x, const int &y) {
        return win[x] > win[y];
    });

    //	for(int i = 1; i <= n; ++i) std::cout << a[i] << ' ';
    //	std::cout << std::endl;

    for (int i = 1; i <= n; ++i)
        s[i] = 0;
    ans[a[1]] = 1, s[a[1]] = 1;
    for (int i = 2; i <= n; ++i)
        if (win[a[i]] == win[a[1]])
            ans[a[i]] = 1, s[a[i]] = 1;

    for (int i = 2; i <= n; ++i) {
        if (ask(a[i])) {
            for (int j = 1; j <= n && win[a[j]] >= win[a[i]]; ++j) {
                ans[a[j]] = 1, s[a[j]] = 1;
            }
        }
    }

    std::cout << "! ";
    for (int i = 1; i <= n; ++i)
        std::cout << ans[i];
    std::cout << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T = 1;

    while (T--) {
        solve();
    }

    return 0;
}