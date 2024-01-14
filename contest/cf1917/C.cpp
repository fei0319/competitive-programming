#include <bits/stdc++.h>

using ll = long long int;

void solve(void) {
    int n, k, d;
    std::cin >> n >> k >> d;

    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }

    std::vector<int> b(k), s(n + 1);
    for (int i = 0; i < k; ++i) {
        std::cin >> b[i];
        s[b[i]] += 1;
    }

    int t = 1;
    for (int i = n; i >= 1; --i) {
        if (i != n)
            s[i] += s[i + 1];
        if (a[i] < i && s[i]) {
            t = std::max(t, (i - a[i] + s[i] - 1) / s[i]);
        }
    }

    int ans = 0;
    int tot = 0;

    std::vector<int> next(n + 1);
    for (int i = 0, p; i < n; i = p) {
        p = i + 1;
        while (p <= n && a[p] > p)
            p += 1;
        if (p > n)
            break;
        next[i] = p;
        if (a[p] == p)
            tot += 1;
    }

    for (int i = 0; i <= std::min(t * k, d - 1); ++i) {
        ans = std::max(ans, tot + (d - i - 1) / 2);

        int now = 0, v = b[i % k];
        while (next[now] && next[now] <= v) {
            a[next[now]] += 1;
            if (a[next[now]] > next[now]) {
                tot -= 1;
                next[now] = next[next[now]];
            } else {
                if (a[next[now]] == next[now]) {
                    tot += 1;
                }
                now = next[now];
            }
        }
    }

    std::cout << ans << '\n';
}

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}