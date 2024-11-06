#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;

const int MAXN = 2e5 + 19;
const int D = 3, P[D] = {int(1e9 + 7), 998244353, 19239481},
          B[D] = {1233, 23214, 19};

int n, q;
std::string s;
int next[MAXN], next_m[MAXN];

int H[D][MAXN], HB[D][MAXN];
int R[D][MAXN], RB[D][MAXN];
void build(std::string s, int n, int h[D][MAXN], int b[D][MAXN]) {
    for (int d = 0; d < D; ++d) {
        b[d][0] = 1, h[d][0] = 0;
        for (int i = 1; i <= n; ++i) {
            b[d][i] = (ll)b[d][i - 1] * B[d] % P[d];
            h[d][i] = ((ll)h[d][i - 1] * B[d] + s[i]) % P[d];
        }
    }
}
std::vector<int> get(int l, int r, int h[D][MAXN], int b[D][MAXN]) {
    std::vector<int> res;
    for (int d = 0; d < D; ++d) {
        int v = (h[d][r] - (ll)h[d][l - 1] * b[d][r - l + 1]) % P[d];
        res.push_back((v + P[d]) % P[d]);
    }
    return res;
}

ll sum(int n) { return (ll)n * (n + 1) / 2; }

ll solve(int l, int r) {
    int n = r - l + 1;
    ll res = 1;
    {
        // even
        if (next[l] > r) {
            // 2 + 4 + 6 + ... +
            res += 2LL * sum((n - 1) / 2);
        }
    }
    {
        // odd
        if (next_m[l] > r && next_m[l + 1] > r) {
            // 3 + 5 + ...
            res += ll(n / 2) * (n / 2) - 1;
        }
    }
    {
        if (get(l, r, H, HB) == get(::n - r + 1, ::n - l + 1, R, RB)) {
            res += n;
        }
    }

    return sum(n) - res;
}

void solve() {
    std::cin >> n >> q;
    std::cin >> s;

    std::string t = s;
    std::reverse(t.begin(), t.end());

    s = ' ' + s;
    t = ' ' + t;

    build(s, n, H, HB);
    build(t, n, R, RB);

    for (int l = 1, r; l <= n; l = r + 1) {
        r = l;
        while (r + 1 <= n && s[r + 1] == s[l]) {
            r += 1;
        }
        for (int i = l; i <= r; ++i) {
            next[i] = r + 1;
        }
    }
    for (int l = 1, r; l <= n; l = r + 2) {
        r = l;
        while (r + 2 <= n && s[r + 2] == s[l]) {
            r += 2;
        }
        for (int i = l; i <= r; i += 2) {
            next_m[i] = r + 2;
        }
    }
    for (int l = 2, r; l <= n; l = r + 2) {
        r = l;
        while (r + 2 <= n && s[r + 2] == s[l]) {
            r += 2;
        }
        for (int i = l; i <= r; i += 2) {
            next_m[i] = r + 2;
        }
    }

    while (q--) {
        int l, r;
        std::cin >> l >> r;
        std::cout << solve(l, r) << '\n';
    }
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