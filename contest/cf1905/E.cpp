#include <bits/stdc++.h>

using ll = long long int;

int const MOD = 998244353;

template <typename T1, typename T2>
struct std::hash<std::pair<T1, T2>> {
    std::size_t operator()(const std::pair<T1, T2> &b) const {
        return std::hash<T1>()(b.first) ^ std::hash<T2>()(b.second);
    }
};

int qpow(int a, ll b) {
    b %= MOD - 1;
    int res = 1;
    while (b) {
        if (b & 1)
            res = (ll)res * a % MOD;
        a = (ll)a * a % MOD, b >>= 1;
    }
    return res;
}

int g(ll n) {
    static std::unordered_map<ll, int> t;
    if (t.contains(n))
        return t[n];
    int res =
        ((ll)qpow(2, n) - qpow(2, n / 2) - qpow(2, (n + 1) / 2) + 1) % MOD;
    if (n > 1) {
        res = (res + 2ll * (g(n / 2) + g((n + 1) / 2))) % MOD;
    } else {
        res = 1;
    }
    return t[n] = res;
}

int f(ll n, bool base) {
    static std::unordered_map<std::pair<ll, bool>, int> t;
    if (t.contains({n, base}))
        return t[{n, base}];
    int res = base ? g(n) : 0;
    if (n > 1) {
        res = ((ll)res + f((n + 1) / 2, false) + f(n / 2, true)) % MOD;
    }
    return t[{n, base}] = res;
}

void solve(void) {
    ll n;
    std::cin >> n;
    std::cout << (f(n, true) + MOD) % MOD << '\n';
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