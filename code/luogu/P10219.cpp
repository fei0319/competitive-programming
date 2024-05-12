#include <bits/stdc++.h>

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
        p += hash_t(*begin + 1) + 17ULL;

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
    int a[12][12]{};
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
                ll power = k - v.size();
                std::vector<int> vals{p};
                for (int i : v) {
                    res = (ll)res * qpow(p, x / p - x / (p * i) + 1) % MOD *
                          qpow(inv[i], x / (p * i)) % MOD * ifact[x / (p * i)] %
                          MOD * fact[x / p] % MOD;
                    power += x / p - x / (p * i) + 1;
                    p *= i;
                    vals.push_back(p);
                }
                // std::cout << res << '\n';
                // for (int i : vals) {
                //     std::cout << i << ' ';
                // }
                // std::cout << "\n";
                res = (ll)res * calc(vals, k - v.size()) % MOD;
                g[x].push_back({ll(res), power});
            }
            // std::cout << std::format("a_{}={}\n", x, a[x]) << std::flush;
        }
    }
    int dp[MAXN], a[MAXN];
    int solve(int n, int b) {
        // std::cout << n << ' ' << b << ' ' << k << '\n';
        for (int x = 1; x <= n; ++x) {
            a[x] = 0;
            for (auto [res, power] : g[x]) {
                a[x] = (a[x] + (ll)res * qpow(b, power)) % MOD;
            }
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

int c, n, m, p[MAXM][MAXN];
int dim[MAXN][MAXM], sz[MAXN];
std::vector<hash_t> par[MAXN];

struct DSU {
    int fa[MAXN];
    void init(int n) {
        std::iota(fa + 1, fa + n + 1, 1);
    }
    int getf(int node) {
        return fa[node] == node ? node : fa[node] = getf(fa[node]);
    }
    bool merge(int x, int y, int d) {
        x = getf(x);
        y = getf(y);
        if (x != y) {
            fa[y] = x;
            dim[x][d] += dim[y][d];
            sz[x] += sz[y];

            assert(par[x] == par[y]);
            return true;
        }
        return false;
    }
} ds[MAXM];

int mv[MAXN], mv_cnt;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    read(c), read(n), read(m), read(S::k);
    for (int i = 1; i <= n * m; ++i) {
        int u, v, w;
        read(u), read(v), read(w);
        p[w][u] = v;
    }

    std::fill(sz + 1, sz + n + 1, 1);
    ds[0].init(n);

    for (int d = 1; d <= m; ++d) {
        ds[d] = ds[d - 1];
        for (int i = 1; i <= n; ++i) {
            dim[i][d] = 1;
        }
        for (int i = 1; i <= n; ++i) {
            ds[d].merge(i, p[d][i], d);
        }
        for (int i = 1; i <= n; ++i) {
            int x = ds[d].getf(i);
            if (x == i && dim[x][d] == 1) {
                int u = x, v = p[d][x];
                mv_cnt = 0;
                for (int t = d - 1; t >= 1; --t) {
                    if (dim[x][t] == 1) {
                        continue;
                    }
                    int len = 0;
                    while (ds[t - 1].getf(u) != ds[t - 1].getf(v)) {
                        u = p[t][u];
                        ++len;
                    }
                    mv[++mv_cnt] = len;
                }
                par[x].push_back(make_hash(mv + 1, mv + mv_cnt + 1));
            }
        }
    }

    std::unordered_map<hash_t, std::pair<int, int>> mt;
    for (int i = 1; i <= n; ++i) {
        int x = ds[m].getf(i);
        if (x == i) {
            hash_t h_d = make_hash(dim[x] + 1, dim[x] + m + 1);
            hash_t h_p = make_hash(par[x].begin(), par[x].end());
            hash_t h = (h_d * 10ULL) ^ (h_p * 19ULL + 21ULL) ^ (h_d * h_p);
            if (!mt.contains(h)) {
                mt[h] = {1, sz[x]};
            } else {
                mt[h].first += 1;
            }
        }
    }

    int N = 1;
    for (auto [_, pair] : mt) {
        N = std::max(N, pair.first);
    }
    S::init(N);

    int ans = 1;
    for (auto [_, pair] : mt) {
        ans = (ll)ans * S::solve(pair.first, pair.second) % MOD;
    }
    ans = (ans + MOD) % MOD;

    std::cout << ans << '\n';
}