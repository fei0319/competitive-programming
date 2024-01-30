#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 1e6 + 19;

using uint = unsigned int;
using BitBase = unsigned long long int;
class Bitset {
    static const uint W = 64;
    std::vector<BitBase> a;
    Bitset(std::vector<BitBase> &&b) : a(b) {}

public:
    Bitset(uint n) {
        a = std::vector<BitBase>(n / W + 1);
    }
    void set(uint pos) {
        a[pos / W] |= 1ULL << (pos % W);
    }
    Bitset &operator|=(const Bitset &b) {
        for (int i = (int)a.size() - 1; i >= 0; --i) {
            a[i] |= b.a[i];
        }
        return *this;
    }
    Bitset operator<<(uint bias) const {
        std::vector<BitBase> x(a.size() + 1);

        for (int i = 0; i + bias / W < (int)a.size(); ++i) {
            if (a[i]) {
                x[i + bias / W] |= a[i] << (bias % W);
                if (bias % W) {
                    x[i + bias / W + 1] |= a[i] >> (W - bias % W);
                }
            }
        }

        return Bitset{std::move(x)};
    }
    uint msb() const {
        for (int i = (int)a.size() - 1; i >= 0; --i) {
            if (a[i]) {
                for (int j = W - 1; j >= 0; --j) {
                    if (a[i] & (1ULL << j)) {
                        return i * W + j;
                    }
                }
            }
        }
        return 0U - 1U;
    }
    void slim(uint n) {
        while (a.size() > n / W + 1) {
            a.pop_back();
        }
        for (int i = n % W + 1; i < W; ++i) {
            if (a[n / W] & (1ULL << i)) {
                a[n / W] ^= 1ULL << i;
            }
        }
    }
};

ll res;
int n, sz[MAXN];
std::vector<int> G[MAXN];

void dfs(int node) {
    for (int to : G[node]) {
        dfs(to);
        sz[node] += sz[to];
    }

    int cnt = 0;
    std::vector<int> a;
    for (int to : G[node]) {
        if (sz[to] == 1) {
            cnt += 1;
        } else {
            a.push_back(sz[to]);
        }
    }

    int x;
    if (a.empty()) {
        x = sz[node] / 2;
    } else {
        int max = *std::max_element(a.begin(), a.end());
        if (max >= sz[node] / 2) {
            x = max;
        } else {
            Bitset dp(sz[node] / 2);
            dp.set(0);
            dp.set(a[0]);
            for (int i = 1; i < (int)a.size(); ++i) {
                dp |= dp << a[i];
            }
            dp.slim(sz[node] / 2);

            x = std::min((int)dp.msb() + cnt, sz[node] / 2);
        }
    }

    res += (ll)x * (sz[node] - x);
    sz[node] += 1;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 2; i <= n; ++i) {
        int p;
        std::cin >> p;
        G[p].push_back(i);
    }

    dfs(1);
    std::cout << res << '\n';

    return 0;
}