#include <bits/stdc++.h>

using ll = long long int;

constexpr int MOD = 1e9 + 7;
constexpr int N = 1e6, MAXN = N + 19;

constexpr int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) {
            res = (ll)res * a % MOD;
        }
        a = (ll)a * a % MOD, b >>= 1;
    }
    return res;
}

int fact[MAXN], ifact[MAXN];
int binom(int n, int m) {
    return (ll)fact[n] * ifact[n - m] % MOD * ifact[m] % MOD;
}

int solve(std::vector<int> a) {
    int ans = 1;
    for (int i = 1; i < a.size(); ++i) {
        int res = (ll)binom(a[i] - 2, a[i] - a[i - 1] - 1) * fact[a[i] - a[i - 1] - 1] % MOD;
        ans = (ll)ans * res % MOD;
    }
    return ans;
}


void solve() {
    int n, m1, m2;
    std::cin >> n >> m1 >> m2;

    std::vector<int> a(m1), b(m2);

    for (int &i : a) {
        std::cin >> i;
    }
    for (int &i : b) {
        std::cin >> i;
    }

    if (a.front() != 1 || b.back() != n || a.back() != b.front()) {
        std::cout << "0\n";
        return;
    }
    for (int &i : b) {
        i = n - i + 1;
    }
    std::reverse(b.begin(), b.end());

    int ans = (ll)solve(a) * solve(b) % MOD;
    ans = (ll)ans * binom(n - 1, a.back() - 1) % MOD;
    std::cout << ans << '\n';
}

int main() {
    fact[0] = 1;
    for (int i = 1; i <= N; ++i) {
        fact[i] = (ll)fact[i - 1] * i % MOD;
    }
    ifact[N] = qpow(fact[N], MOD - 2);
    for (int i = N - 1; i >= 0; --i) {
        ifact[i] = (ll)ifact[i + 1] * (i + 1) % MOD;
    }

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}