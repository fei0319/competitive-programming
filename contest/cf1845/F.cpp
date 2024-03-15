#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 2e5 + 19;

class NTT {
    static constexpr int qpow(int a, int b) {
        int res = 1;
        while (b) {
            if (b & 1) {
                res = (ll)res * a % MOD;
            }
            a = (ll)a * a % MOD, b >>= 1;
        }
        return res;
    }
    static std::vector<int> rev;
    static void dft(std::vector<int>::iterator f, int n, int b) {
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

public:
    static const int MOD = 998244353;
    static std::vector<int> convolution(std::vector<int> f,
                                        std::vector<int> g) {
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
};

std::vector<int> NTT::rev;

const int MOD = 1e9 + 7;

int L, T;
int n, v[MAXN];
std::vector<int> divisor[MAXN * 2];

bool not_prime[MAXN * 2];
int prime[MAXN * 2], cnt;
int mu[MAXN * 2];
void init(int n) {
    mu[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!not_prime[i]) {
            prime[++cnt] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= cnt && i * prime[j] <= n; ++j) {
            not_prime[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                break;
            } else {
                mu[i * prime[j]] = -mu[i];
            }
        }
    }
}

int solve(int x) {
    int res = 0;

    ll N = (ll)T * x / L;
    for (int d : divisor[x]) {
        res = (res + N / d * mu[d]) % MOD;
    }

    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> L >> T;
    L *= 2;

    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> v[i];
    }

    int N = *std::max_element(v + 1, v + 1 + n);
    std::vector<int> f(N + 1);
    for (int i = 1; i <= n; ++i) {
        f[v[i]] = 1;
    }

    auto S = NTT::convolution(f, f);
    for (int i = 1; i <= n; ++i) {
        S[v[i] * 2] = (S[v[i] * 2] - 1) % MOD;
    }

    std::vector<int> g(N + 1);
    for (int i = 1; i <= n; ++i) {
        g[N - v[i]] = 1;
    }
    g = NTT::convolution(f, g);
    for (int i = N; i < g.size(); ++i) {
        S[i - N] = (S[i - N] + g[i]) % NTT::MOD;
    }

    for (int i = 1; i <= N * 2; ++i) {
        for (int j = i; j <= N * 2; j += i) {
            divisor[j].push_back(i);
        }
    }

    std::vector<uint8_t> vist(N * 2 + 1);
    for (int i = 1; i < S.size(); ++i) {
        if (S[i] % NTT::MOD != 0) {
            for (int d : divisor[i]) {
                vist[d] = true;
            }
        }
    }

    init(N * 2);
    int ans = 0;
    for (int i = 1; i <= N * 2; ++i) {
        if (vist[i]) {
            ans = (ans + solve(i)) % MOD;
        }
    }
    std::cout << ans << '\n';

    return 0;
}