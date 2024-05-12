#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using uint = unsigned int;

const int MAXN = 1e6 + 19;

uint zero;
uint ans = 1;
uint x, q, M;
uint k[MAXN];

uint qpow(uint a, uint b) {
    uint res = 1;
    while (b) {
        if (b & 1)
            res = (ll)res * a % M;
        a = (ll)a * a % M, b >>= 1;
    }
    return res;
}

uint prime[MAXN], cnt;
bool vist[MAXN];
void init(const int &N) {
    for (int i = 2; i <= N; ++i) {
        if (!vist[i]) {
            prime[++cnt] = i;
        }
        for (int j = 1; j <= cnt && i * prime[j] <= N; ++j) {
            vist[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}

void add(uint x) {
    std::vector<std::pair<uint, uint>> a;
    for (uint i = 1; prime[i] * prime[i] <= x; ++i) {
        uint v = prime[i];
        if (x % v == 0) {
            uint p = 0;
            while (x % v == 0) {
                p += 1;
                x /= v;
            }
            a.emplace_back(v, p);
        }
    }
    if (x > 1) {
        a.emplace_back(x, 1);
    }

    for (auto [v, p] : a) {
        if (v == 2)
            continue;
        if (v < MAXN) {
            if ((k[v] + 1) % M) {
                ans = (ull)ans * qpow(k[v] + 1, M - 2) % M;
            } else {
                zero -= 1;
            }

            k[v] += p;
            if ((k[v] + 1) % M) {
                ans = (ull)ans * (k[v] + 1) % M;
            } else {
                zero += 1;
            }
        } else {
            ans = (ull)ans * (p + 1) % M;
        }
    }
}

int main() {
    init(1e6);

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> x >> q >> M;
    add(x);

    while (q--) {
        std::cin >> x;
        add(x);
        std::cout << (zero ? 0U : ans) << '\n';
    }

    return 0;
}