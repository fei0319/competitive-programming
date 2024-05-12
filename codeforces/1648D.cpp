#include <bits/stdc++.h>

using ll = long long int;
constexpr int MAXN = 5e5 + 19;
constexpr ll INF = 1e18;

int n, q;
int a[4][MAXN];
ll s[4][MAXN];

ll src[MAXN], dp[MAXN];

struct Node {
    int l, r, k;
} node[MAXN];
ll maxv[MAXN];

void solve(int l, int r, std::vector<int> p, ll k) {
    if (l == r) {
        for (int i : p) {
            dp[l] = std::max(dp[l], maxv[i] - node[i].k);
        }
        for (int i : p) {
            maxv[i] = std::max({maxv[i], dp[l], src[l]});
        }
        return;
    }

    int mid = (l + r) / 2;

    std::vector<int> L, R, W;
    for (int i : p) {
        if (node[i].l <= l && r <= node[i].r) {
            W.push_back(i);
            k = std::min(k, (ll)node[i].k);
        } else {
            if (node[i].l <= mid) {
                L.push_back(i);
            }
            if (node[i].r > mid) {
                R.push_back(i);
            }
        }
    }

    ll res = -INF;
    for (int i : W) {
        res = std::max(res, maxv[i] - node[i].k);
    }
    for (int i = l; i <= r; ++i) {
        dp[i] = std::max(dp[i], res);
    }

    solve(l, mid, L, k);

    res = -INF;
    for (int i = l; i <= r; ++i) {
        dp[i] = std::max(dp[i], res - k);
        res = std::max({res, dp[i], src[i]});
    }

    solve(mid + 1, r, R, k);

    res = std::max(*std::max_element(dp + l, dp + r + 1),
                   *std::max_element(src + l, src + r + 1));
    for (int i : W) {
        maxv[i] = std::max(maxv[i], res);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> q;
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= n; ++j) {
            std::cin >> a[i][j];
            s[i][j] = s[i][j - 1] + a[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        src[i] = s[1][i + 1] - s[2][i];
    }
    src[n] = -INF;
    std::fill(dp, dp + n + 1, -INF);

    std::vector<int> p(q);
    std::iota(p.begin(), p.end(), 0);
    for (int i : p) {
        std::cin >> node[i].l >> node[i].r >> node[i].k;
        node[i].l -= 1;
        maxv[i] = -INF;
    }
    solve(0, n, p, INF);

    ll ans = -INF;
    for (int i = 1; i <= n; ++i) {
        ans = std::max(ans, dp[i] + s[2][i] + s[3][n] - s[3][i - 1]);
    }
    std::cout << ans << '\n';

    return 0;
}