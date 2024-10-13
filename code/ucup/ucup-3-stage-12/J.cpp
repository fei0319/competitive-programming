#include <bits/stdc++.h>

using i64 = int64_t;
using i128 = __int128_t;
constexpr i64 MOD = i64(1e18) + 9, MAGIC = 1004535809998244353;

template <typename T>
void exgcd(T a, T b, T &x, T &y) {
    if (!b) {
        x = 1, y = 0;
        return;
    }
    exgcd(b, a % b, y, x);
    y -= a / b * x;
}

// dp[x] = sum(g(dp[s])) + sz[x]
i64 g(i64 v) {
    return (i128)v * (v ^ MAGIC) * 2 % MOD;
}

struct Division {
    i64 core, branch;
};

struct Tree {
    int n, rt;
    std::vector<std::vector<int>> adj;
    std::vector<int> sz;
    std::vector<i64> dp;
    std::vector<std::vector<i64>> pre;

    void swap(Tree &other) {
        std::swap(n, other.n);
        std::swap(rt, other.rt);
        adj.swap(other.adj);
        sz.swap(other.sz);
        dp.swap(other.dp);
        pre.swap(other.pre);
    }

    explicit Tree(int n) : n(n), adj(n), sz(n), dp(n), pre(n) {}

    void init() {
        std::vector<int> p(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> p[i];
            --p[i];
        }

        for (int i = 0; i < n; ++i) {
            if (p[i] == -1) {
                rt = i;
            } else {
                adj[p[i]].push_back(i);
            }
        }

        auto dfs = [&](auto &self, int node) -> void {
            sz[node] = 1;
            for (int to : adj[node]) {
                self(self, to);
            }

            std::sort(adj[node].begin(), adj[node].end(), [&](int x, int y) {
                return sz[x] < sz[y];
            });
            pre[node].resize(adj[node].size());
            i64 sum = 0;
            for (int i = 0; i < adj[node].size(); ++i) {
                int to = adj[node][i];
                sum = (sum + g(dp[to])) % MOD;
                sz[node] += sz[to];
                pre[node][i] = (sum + sz[node]) % MOD;
            }
            dp[node] = (sum + sz[node]) % MOD;
        };
        dfs(dfs, rt);
    }

    Division divide(int k, int x) {
        if (k == 1) {
            return Division{dp[x], 1};
        }
        auto dfs = [&](auto &self, int node) -> Division {
            if (sz[node] % k != 0) {
                return Division{-1, -1};
            }
            if (sz[node] == k) {
                return Division{1, dp[node]};
            }
            int l = adj[node].size(), tot = 0;
            while (l - 1 >= 0 && sz[adj[node][l - 1]] >= k) {
                tot += sz[adj[node][--l]];
            }
            if (sz[node] - tot != k) {
                return Division{-1, -1};
            }
            i64 core = sz[node] / k;
            i64 branch = pre[node][l - 1];
            for (int i = l; i < adj[node].size(); ++i) {
                int to = adj[node][i];
                auto [ncore, nbranch] = self(self, to);
                if (nbranch != branch) {
                    return Division{-1, -1};
                }
                core = (core + g(ncore)) % MOD;
            }
            return Division{core, branch};
        };
        return dfs(dfs, x);
    }

    std::vector<int> find(i64 v) {
        for (int x = 0; x < n; ++x) {
            if (dp[x] != v) {
                continue;
            }
            std::vector<int> all;
            auto dfs = [&](auto &self, int node) -> void {
                all.push_back(node);
                for (int to : adj[node]) {
                    self(self, to);
                }
            };
            dfs(dfs, x);

            std::vector<int> id(n);
            for (int i = 0; i < all.size(); ++i) {
                id[all[i]] = i + 1;
            }

            std::vector<int> p(all.size());
            for (int f : all) {
                for (int s : adj[f]) {
                    if (id[s] != -1) {
                        p[id[s] - 1] = id[f];
                    }
                }
            }
            return p;
        }
        return {};
    }
};

bool test(int &x) {
    if (x) {
        --x;
        return true;
    }
    return false;
}

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    int a, b, c;
    std::cin >> a >> b >> c;

    Tree A(a), B(b), C(c);
    A.init();
    B.init();
    C.init();

    if ((c + 1) % std::gcd(a, b) != 0) {
        std::cout << "Impossible\n";
        return;
    }

    auto check = [&](int x, int y, bool rev) -> bool {
        // if (!rev)
        //     std::cout << "checking " << x << ' ' << y << '\n';
        // else
        //     std::cout << "checking " << y << ' ' << x << " (rev)" << '\n';

        std::vector<int> son = C.adj[C.rt];
        std::vector<std::array<Division, 2>> res(
            son.size(), {Division{-1, -1}, Division{-1, -1}});
        std::vector<int> order;
        for (int i = son.size() - 1; i >= 0; --i) {
            int to = son[i];
            int sz = C.sz[to];
            if (sz < x && sz < y) {
                break;
            }
            if ((sz >= x && sz % x != 0) && (sz >= y && sz % y != 0)) {
                return false;
            }
            res[i][0] = C.divide(x, to);
            res[i][1] = C.divide(y, to);
            order.push_back(i);
        }

        auto [div_a, div_b] = res[res.size() - 1];
        if (div_a.branch == -1) {
            return false;
        }
        i64 branch_A = div_a.branch, branch_B = -1;

        std::map<i64, int> need_A, need_B;
        for (int to : A.adj[A.rt]) {
            need_A[A.dp[to]] += 1;
        }
        for (int to : B.adj[B.rt]) {
            need_B[B.dp[to]] += 1;
        }

        // std::cout << "A: ";
        // for (auto [k, c] : need_A) {
        //     std::cout << k << ' ';
        // }
        // std::cout << '\n';
        // std::cout << "B: ";
        // for (auto [k, c] : need_B) {
        //     std::cout << k << ' ';
        // }
        // std::cout << '\n';

        std::shuffle(order.begin(), order.end(), rng);

        i64 sum_dp = (C.dp[C.rt] - C.sz[C.rt] + MOD) % MOD;
        for (int i : order) {
            auto [div_a, div_b] = res[i];
            // std::cout << "provides: " << div_a.core << ' ' << div_b.core
            //           << '\n';

            if (div_a.branch == branch_A && test(need_A[div_a.core])) {
                sum_dp = (sum_dp - g(C.dp[son[i]]) + MOD) % MOD;
                continue;
            } else {
                if (div_b.branch == -1) {
                    continue;
                }
                if ((branch_B == -1 || branch_B == div_b.branch) &&
                    test(need_B[div_b.core])) {
                    branch_B = div_b.branch;
                    sum_dp = (sum_dp - g(C.dp[son[i]]) + MOD) % MOD;
                    continue;
                }
            }
        }

        for (auto [k, c] : need_A) {
            if (c) {
                return false;
            }
        }
        for (auto [k, c] : need_B) {
            if (c) {
                return false;
            }
        }

        if (sum_dp != (branch_A + branch_B - x - y + MOD) % MOD) {
            return false;
        }

        auto X = C.find(branch_A), Y = C.find(branch_B);
        assert(X.size() == x);
        assert(Y.size() == y);

        if (rev) {
            X.swap(Y);
        }

        std::cout << X.size() << ' ' << Y.size() << '\n';
        for (int i : X) {
            std::cout << i << ' ';
        }
        std::cout << '\n';
        for (int i : Y) {
            std::cout << i << ' ';
        }
        std::cout << '\n';

        return true;
    };

    i64 x, y;
    exgcd<i64>(a, b, x, y);
    {
        int g = std::gcd(a, b);
        x *= (c + 1) / g;
        y *= (c + 1) / g;

        i64 dx = b / g;
        i64 dy = a / g;
        {
            i64 k = x / dx;
            x -= k * dx;
            y += k * dy;
        }
        if (x <= 0) {
            x += dx;
            y -= dy;
        }

        while (y > 0) {
            A.swap(B);
            for (int _ = 0; _ < 5; ++_) {
                if (check(y, x, true)) {
                    return;
                }
            }
            A.swap(B);
            for (int _ = 0; _ < 5; ++_) {
                if (check(x, y, false)) {
                    return;
                }
            }

            x += dx;
            y -= dy;
        }
    }

    std::cout << "Impossible\n";
}

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }
}
