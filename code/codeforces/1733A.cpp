// Problem: A. Consecutive Sum
// Contest: Codeforces Round #821 (Div. 2)
// URL: https://codeforces.com/contest/1733/problem/A
// Memory Limit: 256 MB
// Time Limit: 1000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

constexpr int maxn = 100 + 9;

int n, k, a[maxn], cnt[maxn];
std::vector<int> all[maxn];

void solve() {
    std::cin >> n >> k;

    for (int i = 0; i < k; ++i) {
        all[i].clear();
        cnt[i] = 0;
    }

    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        all[i % k].emplace_back(a[i]);
    }

    for (int i = 0; i < k; ++i) {
        std::sort(all[i].begin(), all[i].end());
        std::reverse(all[i].begin(), all[i].end());
    }

    long long int ans = 0, res = 0;

    for (int i = 1; i <= k; ++i) {
        res += all[i % k][cnt[i % k]++];
    }
    ans = res;

    std::cout << ans << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}