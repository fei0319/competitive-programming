#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 1e6 + 19, MOD = 998244353;

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

int n, q;
int a[MAXN], b[MAXN];

int A, B;
int fact[MAXN], ifact[MAXN], s[MAXN], half[MAXN];
int binom(int n, int m) {
    return (ll)fact[n] * ifact[n - m] % MOD * ifact[m] % MOD;
}
void init(int N) {
    fact[0] = 1;
    for (int i = 1; i <= N; ++i) {
        fact[i] = (ll)fact[i - 1] * i % MOD;
    }
    ifact[N] = qpow(fact[N], MOD - 2);
    for (int i = N - 1; i >= 0; --i) {
        ifact[i] = (ll)ifact[i + 1] * (i + 1) % MOD;
    }

    s[0] = binom(N, 0);
    for (int i = 1; i <= N; ++i) {
        s[i] = (s[i - 1] + binom(N, i)) % MOD;
    }

    half[0] = 1;
    half[1] = qpow(2, MOD - 2);
    for (int i = 2; i <= N; ++i) {
        half[i] = (ll)half[i - 1] * half[1] % MOD;
    }
}

struct BIT {
    ll tr[MAXN];
    void update(int x, int k) {
        for (; x < MAXN; x += x & -x) {
            tr[x] += k;
        }
    }
    ll query(int x) {
        ll res = 0;
        for (; x; x -= x & -x) {
            res += tr[x];
        }
        return res;
    }
    ll query(ll l, ll r) {
        return query(r) - query(l - 1);
    }
} mA, mB;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        A += a[i];
        mA.update(i, a[i]);
    }
    for (int i = 1; i <= n; ++i) {
        std::cin >> b[i];
        B += b[i];
        mB.update(i, b[i]);
    }

    init(B);
    while (q--) {
        int l, r;
        std::cin >> l >> r;

        int a1 = mA.query(l, r), b1 = mB.query(l, r);
        int a2 = A - a1;

        int t = std::min(B, b1 + a1 - a2 - 1);
        if (t < 0) {
            std::cout << "0 ";
            continue;
        }

        int ans = (ll)half[B] * s[t] % MOD;
        std::cout << (ans + MOD) % MOD << " ";

    }

    return 0;
}