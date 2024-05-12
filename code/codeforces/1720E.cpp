#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 5e2 + 19;

int n, k, a[MAXN][MAXN];

int count_colors() {
    std::vector<int> t;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            t.push_back(a[i][j]);
        }
    }
    std::sort(t.begin(), t.end());
    return std::unique(t.begin(), t.end()) - t.begin();
}

struct Submatrix {
    int x1, y1;
    int x2, y2;
    bool has_value() const {
        return x1 != 0;
    }
} mat[MAXN * MAXN];
void update(int c, int x, int y) {
    if (mat[c].has_value()) {
        mat[c].x1 = std::min(mat[c].x1, x);
        mat[c].y1 = std::min(mat[c].y1, y);
        mat[c].x2 = std::max(mat[c].x2, x);
        mat[c].y2 = std::max(mat[c].y2, y);
    } else {
        mat[c] = {x, y, x, y};
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            std::cin >> a[i][j];
        }
    }

    int tot = count_colors();
    if (tot <= k) {
        std::cout << k - tot << '\n';
        return 0;
    }

    if (k == 1) {
        std::cout << "1\n";
        return 0;
    }

    // the answer will be either 1 or 2
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            update(a[i][j], i, j);
        }
    }

    std::vector<Submatrix> all;
    for (int i = 1; i <= n * n; ++i) {
        if (mat[i].has_value()) {
            all.push_back(mat[i]);
        }
    }
    assert(tot == all.size());
    for (int x = 1; x <= n; ++x) {
        std::vector<Submatrix> b;
        for (auto i : all) {
            if (i.x1 >= x) {
                b.push_back(i);
            }
        }
        std::sort(b.begin(), b.end(), [](const auto &u, const auto &v) {
            return u.x2 > v.x2;
        });
        // now b.back() has the minimum x2

        static int positive[MAXN], negative[MAXN];
        std::fill(positive, positive + n + 1, 0);
        std::fill(negative, negative + n + 1, 0);

        std::vector<std::vector<std::pair<int, int>>> q(n + 1);
        for (int L = 1; x + L - 1 <= n && L < n; ++L) {
            while (!b.empty() && x + L - 1 >= b.back().x2) {
                auto [x1, y1, x2, y2] = b.back();
                b.pop_back();

                if (y2 - y1 + 1 > L) {
                    q[y2 - y1 + 1].emplace_back(y1, y2);
                } else {
                    positive[y2] += 1;
                    negative[y1 + 1] += 1;
                }
            }
            for (auto [y1, y2] : q[L]) {
                positive[y2] += 1;
                negative[y1 + 1] += 1;
            }

            int val = 0;
            for (int y = 1; y < L; ++y) {
                val += positive[y];
            }
            for (int y = 1; y + L - 1 <= n; ++y) {
                val += positive[y + L - 1];
                val -= negative[y];

                if (tot - val <= k && tot - val >= k - 1) {
                    std::cout << "1\n";
                    return 0;
                }
            }
        }
    }

    std::cout << "2\n";
    return 0;
}