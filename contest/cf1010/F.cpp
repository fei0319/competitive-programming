#include <bits/stdc++.h>

using ll = long long int;

constexpr int MOD = 998244353;

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

using poly = std::vector<int>;

namespace NTT {
    std::vector<int> rev;
    void dft(poly::iterator f, int n, int b) {
        std::vector<int> w(n);
        for (int i = 0; i < n; ++i) {
            if (i < rev[i]) {
                std::swap(f[i], f[rev[i]]);
            }
        }
        for (int i = 2; i <= n; i <<= 1) {
            w[0] = 1, w[1] = qpow(3, (MOD - 1) / i);
            if (b == -1) {
                w[1] = qpow(w[1], MOD - 2);
            }
            for (int j = 2; j < i / 2; ++j) {
                w[j] = (ll)w[j - 1] * w[1] % MOD;
            }
            for (int j = 0; j < n; j += i) {
                auto g = f + j, h = f + j + i / 2;
                for (int k = 0; k < i / 2; ++k) {
                    int p = g[k], q = (ll)h[k] * w[k] % MOD;
                    g[k] = (p + q) % MOD, h[k] = (p - q) % MOD;
                }
            }
        }
    }

    poly add(const poly &f, const poly &g) {
        poly res(f);
        if (res.size() < g.size()) {
            res.resize(g.size());
        }
        for (int i = 0; i < g.size(); ++i) {
            res[i] = (res[i] + g[i]) % MOD;
        }
        return res;
    }

    poly convolution(poly f, poly g) {
        int N = 1, n = f.size() + g.size() - 1;

        while (N < n) {
            N <<= 1;
        }
        rev.resize(N);
        rev[0] = 0;
        for (int i = 1; i < N; ++i) {
            rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? N >> 1 : 0);
        }

        f.resize(N);
        g.resize(N);
        dft(f.begin(), N, 1);
        dft(g.begin(), N, 1);
        for (int i = 0; i < N; ++i) {
            f[i] = (ll)f[i] * g[i] % MOD;
        }
        dft(f.begin(), N, -1);
        f.resize(n);

        const int inv = qpow(N, MOD - 2);
        for (auto &i : f) {
            i = (ll)i * inv % MOD;
        }
        return f;
    }
} // namespace NTT

constexpr int MAXN = 1e5 + 19;

int n;
ll x;
std::vector<int> G[MAXN];

int son[MAXN], size[MAXN];
void dfs1(int node, int f) {
    size[node] = 1;
    G[node].resize(std::remove(G[node].begin(), G[node].end(), f) -
                   G[node].begin());
    for (int to : G[node]) {
        dfs1(to, node);
        if (size[to] > size[son[node]]) {
            son[node] = to;
        }
        size[node] += size[to];
    }
}

std::pair<poly, poly> solve(std::vector<poly>::iterator f, int l, int r) {
    if (l == r) {
        return {f[l], f[l]};
    }
    int mid = (l + r) / 2;

    auto L = solve(f, l, mid), R = solve(f, mid + 1, r);
    L.second = NTT::add(L.second, NTT::convolution(L.first, R.second));
    L.first = NTT::convolution(L.first, R.first);
    return L;
}

poly solve(int node) {
    int x = node;
    std::vector<int> p{x};
    while (son[x]) {
        x = son[x];
        p.push_back(x);
    }

    std::vector<poly> f(p.size());
    for (int i = 0; i < p.size(); ++i) {
        if (G[p[i]].size() <= 1) {
            f[i] = poly{0, 1};
        } else if (G[p[i]].size() == 2) {
            int v = G[p[i]][0];
            if (v == son[p[i]]) {
                v = G[p[i]][1];
            }
            f[i] = solve(v);
            f[i].insert(f[i].begin(), 0);
        } else {
            assert(false);
        }
    }

    auto res = solve(f.begin(), 0, f.size() - 1).second;
    res[0] = (res[0] + 1) % MOD;
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> x;
    for (int i = 2; i <= n; ++i) {
        int u, v;
        std::cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs1(1, 0);
    poly f = solve(1);

    int ans = 0, b = 1;
    for (int i = 1; i <= n; ++i) {
        ans = (ans + (ll)b * f[i]) % MOD;

        b = (ll)b * (x % MOD + i) % MOD;
        b = (ll)b * qpow(i, MOD - 2) % MOD;
    }

    std::cout << (ans + MOD) % MOD << '\n';

    return 0;
}