#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 2e5 + 19, MAXA = 1e6 + 19, B = 18;

int n, q, a[MAXN];
int next[MAXN][B], last_pos[MAXA];

void solve() {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        last_pos[a[i]] = 0;
    }
    for (int i = n; i >= 1; --i) {
        next[i][0] = last_pos[a[i]];
        last_pos[a[i]] = i;
        for (int j = 1; j < B; ++j) {
            next[i][j] = next[next[i][j - 1]][j - 1];
        }
    }

    std::cin >> q;
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        int x = l;
        for (int i = B - 1; i >= 0; --i) {
            if (next[x][i] - x == (1 << i)) {
                x = next[x][i];
            }
        }
        if (x + 1 <= r) {
            std::cout << l << ' ' << x + 1 << '\n';
        } else {
            std::cout << "-1 -1\n";
        }
    }
    std::cout << '\n';
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