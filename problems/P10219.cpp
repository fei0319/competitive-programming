#ifdef ONLINE_JUDGE
#include <bits/stdc++.h>
#endif
#include <array>
#include <cstdint>
#include <functional>
#include <iostream>
#include <numeric>
#include <random>
#include <unordered_map>
#include <vector>

template <class T>
void read(T &res) {
    char ch;
    std::cin.get(ch);
    res = 0;
    while (!isdigit(ch)) {
        std::cin.get(ch);
    }
    while (isdigit(ch)) {
        res = res * 10 + (ch - 48);
        std::cin.get(ch);
        if (std::cin.eof()) {
            break;
        }
    }
}

using hash_t = uint64_t;
template <class Iter>
hash_t make_hash(Iter begin, Iter end) {
    hash_t res = 0, p = 0;
    while (begin != end) {
        res ^= hash_t(*begin) * 998244353ULL + p * 19ULL;
        res += (p + 89ULL) * 1004535989ULL;
        p += hash_t(*begin + 1) * 3ULL + 7ULL;

        ++begin;
    }
    return res;
}

using ll = int64_t;

constexpr int MOD = 998244353;
constexpr int MAXN = 2e3 + 19;
constexpr int MAXM = 1e3 + 19;

struct Matrix {
    int N;
    std::array<std::array<int, 12>, 12> a{};
    Matrix(int n) {
        N = n;
    }
    static Matrix E(int n) {
        Matrix res(n);
        for (int i = 0; i < n; ++i) {
            res.a[i][i] = 1;
        }
        return res;
    }
    Matrix operator*(const Matrix &rhs) const {
        Matrix res(N);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    res.a[i][k] =
                        (res.a[i][k] + (ll)a[i][j] * rhs.a[j][k]) % MOD;
                }
            }
        }
        return res;
    }
};

Matrix qpow(Matrix a, ll b) {
    Matrix res = Matrix::E(a.N);
    while (b) {
        if (b & 1)
            res = res * a;
        a = a * a, b >>= 1;
    }
    return res;
}

constexpr int qpow(int a, ll b) {
    int res = 1;
    while (b) {
        if (b & 1)
            res = (ll)res * a % MOD;
        a = (ll)a * a % MOD, b >>= 1;
    }
    return res;
}

namespace S {
    ll k;
    std::vector<std::vector<int>> f[MAXN];
    std::vector<std::array<ll, 2>> g[MAXN];
    int fact[MAXN], ifact[MAXN], inv[MAXN];
    int calc(std::vector<int> v, ll k) {
        Matrix t(v.size());
        for (int i = 0; i < v.size(); ++i) {
            for (int j = i; j < v.size(); ++j) {
                t.a[i][j] = v[j];
            }
        }
        auto res = qpow(t, k);
        int ans = 0;
        for (int i = 0; i < v.size(); ++i) {
            ans = (ans + res.a[0][i]) % MOD;
        }

        return ans;
    }
    void init(int N) {
        f[1].push_back({});
        for (int i = 2; i <= N; ++i) {
            f[i].push_back(std::vector<int>{i});
            for (int j = 2; j < i; ++j) {
                if (i % j == 0) {
                    for (const auto &v : f[j]) {
                        f[i].push_back(v);
                        f[i].back().push_back(i / j);
                    }
                }
            }
        }
        fact[0] = 1;
        for (int i = 1; i <= N; ++i) {
            fact[i] = (ll)fact[i - 1] * i % MOD;
        }
        ifact[N] = qpow(fact[N], MOD - 2);
        for (int i = N - 1; i >= 0; --i) {
            ifact[i] = (ll)ifact[i + 1] * (i + 1) % MOD;
        }
        for (int i = 1; i <= N; ++i) {
            inv[i] = (ll)ifact[i] * fact[i - 1] % MOD;
        }

        for (int x = 1; x <= N; ++x) {
            for (const auto &v : f[x]) {
                if (k < v.size()) {
                    continue;
                }
                int res = 1, p = 1;
                std::vector<int> vals{p};
                for (int i : v) {
                    res = (ll)res * qpow(inv[i], x / p / i) % MOD *
                          fact[x / p] % MOD;
                    p *= i;
                    vals.push_back(p);
                }
                res = (ll)res * calc(vals, k - v.size()) % MOD;

                g[x].push_back(
                    {ll(res), k - (ll)v.size() +
                                  std::accumulate(v.begin(), v.end(), 0)});
            }
        }
    }
    int dp[MAXN], a[MAXN];
    int solve(int n, int b) {
        // std::cout << n << ' ' << b << ' ' << k << '\n';

        for (int x = 1; x <= n; ++x) {
            int ans = 0;
            for (const auto &v : g[x]) {
                ans = (ans + v[0] * qpow(b, v[1])) % MOD;
            }
            a[x] = ans;

            // std::cout << "a_" << x << "=" << a[x] << '\n';
        }

        std::fill(dp, dp + n + 1, 0);
        dp[0] = 1;
        for (int x = 1; x <= n; ++x) {
            for (int i = n; i >= 1; --i) {
                int v = 1, b = (ll)a[x] * ifact[x] % MOD;
                for (int j = 1; i - j * x >= 0; ++j) {
                    v = (ll)v * b % MOD;
                    dp[i] =
                        (dp[i] + (ll)dp[i - j * x] * v % MOD * ifact[j]) % MOD;
                }
            }
        }

        return (ll)dp[n] * fact[n] % MOD;
    }
} // namespace S

int c, n, m;

int fa[MAXN], dim[MAXN][MAXM];
std::vector<int> sub[MAXN];
int getf(int node) {
    return node == fa[node] ? node : fa[node] = getf(fa[node]);
}
int p[MAXM][MAXN];

struct Node {
    hash_t dim_hash;
    std::vector<std::vector<int>> a;
    bool check(int x, ll h) {
        if (h != dim_hash) {
            return false;
        }
        return true;
    }
};
std::vector<Node> components;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    read(c), read(n), read(m), read(S::k);
    for (int i = 1; i <= n * m; ++i) {
        int u, v, w;
        read(u), read(v), read(w);
        p[w][u] = v;
    }
    S::init(n);

    std::iota(fa + 1, fa + n + 1, 1);
    for (int i = 1; i <= n; ++i) {
        sub[i].push_back(i);
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            dim[j][i] = 1;
        }
        for (int j = 1; j <= n; ++j) {
            if (getf(j) != getf(p[i][j])) {
                int u = getf(j), v = getf(p[i][j]);
                if (sub[u].size() < sub[v].size()) {
                    std::swap(u, v);
                }
                fa[v] = u;
                dim[u][i] += dim[v][i];
                sub[u].insert(sub[u].end(), sub[v].begin(), sub[v].end());
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (getf(i) == i) {
            auto &v = sub[i];
            auto h = make_hash(dim[i] + 1, dim[i] + m + 1);
            bool ok = false;
            for (auto &component : components) {
                if (component.check(i, h)) {
                    component.a.push_back(v);
                    ok = true;
                    break;
                }
            }
            if (!ok) {
                components.push_back(Node{});
                components.back().a.push_back(v);
                components.back().dim_hash = h;
            }
        }
    }

    int ans = 1;
    for (auto &component : components) {
        int n = component.a.size(), b = component.a[0].size();
        ans = (ll)ans * S::solve(n, b) % MOD;
    }
    ans = (ans + MOD) % MOD;

    std::cout << ans << '\n';
}