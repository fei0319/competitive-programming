#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 3e5 + 19, maxs = 256;

int n, to[4][maxs], dp[maxs], a[maxn], len[maxs];

void trans(int x) {
    static int tmp[maxs];
    for (int i = 0; i < maxs; ++i) tmp[i] = 0;
    for (int i = 0; i < maxs; ++i) tmp[to[x][i]] += dp[i];
    for (int i = 0; i < maxs; ++i) dp[i] = tmp[i];
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];

    for (int s = 0; s < maxs; ++s) {
        if (s == 0) len[s] = 0;
        else if (s < 4) len[s] = 1;
        else if (s < 16) len[s] = 2;
        else if (s < 64) len[s] = 3;
        else if (s < 256) len[s] = 4;

        int t1 = s % 4, t2 = s / 4 % 4, t3 = s / 16 % 4, t4 = s / 64 % 4;
        for (int x = 0; x < 4; ++x) {
            int n1 = t1, n2 = t2, n3 = t3, n4 = t4;
            if (!t1 || (x & t1)) n1 = x;
            else if (!t2 || (x & t2)) n2 = x;
            else if (!t3 || (x & t3)) n3 = x;
            else n4 = x;
            to[x][s] = n1 + n2 * 4 + n3 * 16 + n4 * 64;
        }
    }

    ll ans = 0ll;
    for (int i = 1; i <= n; ++i) {
        if (a[i] == 0) ans += (ll)i * (n - i + 1);
        trans(a[i]);
        ++dp[a[i]];
        for (int s = 0; s < maxs; ++s) ans += (ll)dp[s] * len[s];
    }

    std::cout << ans << std::endl;

    return 0;
}