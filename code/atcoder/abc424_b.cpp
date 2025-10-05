#include <bits/stdc++.h>

void solve() {
    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<int> cnt(n + 1);
    while (k--) {
        int a, b;
        std::cin >> a >> b;
        cnt[a] += 1;
        if (cnt[a] == m) {
            std::cout << a << " ";
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();
}
