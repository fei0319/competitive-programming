#include <algorithm>
#include <iostream>
#include <vector>

constexpr int MAXN = 2e5 + 19;

namespace sg {
int max[MAXN << 2];

void push_up(int node) {
    max[node] = std::max(max[node << 1], max[node << 1 | 1]);
}

void build(int node, int L, int R) {
    max[node] = 0;
    if (L == R) {
        return;
    }
    int mid = (L + R) / 2;
    build(node << 1, L, mid);
    build(node << 1 | 1, mid + 1, R);
}

int query(int node, int L, int R, int l, int r) {
    if (l <= L && R <= r) {
        return max[node];
    }
    int mid = (L + R) / 2;
    int res = 0;
    if (l <= mid) {
        res = std::max(res, query(node << 1, L, mid, l, r));
    }
    if (r > mid) {
        res = std::max(res, query(node << 1 | 1, mid + 1, R, l, r));
    }
    return res;
}

void modify(int node, int L, int R, int x, const int &val) {
    max[node] = std::max(max[node], val);
    if (L == R) {
        return;
    }
    int mid = (L + R) / 2;
    if (x <= mid) {
        modify(node << 1, L, mid, x, val);
    } else {
        modify(node << 1 | 1, mid + 1, R, x, val);
    }
}

} // namespace sg

int n, m;
std::vector<int> a[MAXN];

int s[MAXN];
int dp[MAXN], next[MAXN];
int last_pos[MAXN];

std::vector<int> v;
bool vist[MAXN];
void clear() {
    for (int i : v) {
        vist[i] = false;
    }
    v.clear();
}

void solve() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        int k;
        std::cin >> k;
        a[i].resize(k);
        for (int j = 0; j < k; ++j) {
            std::cin >> a[i][j];
        }
    }

    bool has_empty = false;
    int last_empty = n + 1;

    s[n + 1] = 0;
    next[n + 1] = n + 1;
    dp[n + 1] = 0;
    sg::build(1, 1, n + 1);
    for (int i = n; i >= 1; --i) {
        if (a[i].empty()) {
            has_empty = true;
        }
        s[i] = s[i + 1] + a[i].size();

        next[i] = next[i + 1];
        for (int j : a[i]) {
            if (last_pos[j]) {
                next[i] = std::min(next[i], last_pos[j]);
            }
            last_pos[j] = i;
        }
        if (next[i] != n + 1) {
            dp[i] = dp[next[i] + 1];
        } else {
            if (has_empty) {
                dp[i] = m;
            } else {
                dp[i] = s[i];
            }
        }

        if (a[i].empty()) {
            last_empty = i;
        }
        int l = last_empty + 1, r = next[i];
        if (l == i + 1) {
            l = i + 2;
        }

        if (l <= r) {
            dp[i] = std::max(dp[i], sg::query(1, 1, n + 1, l, r));
        }
        sg::modify(1, 1, n + 1, i, dp[i]);
    }

    int ans = dp[1];
    has_empty = false;
    for (int i = 1; i <= n; ++i) {
        if (a[i].empty()) {
            has_empty = true;
        }
        for (int j : a[i]) {
            if (vist[j]) {
                clear();
                has_empty = false;
                ans = std::max(ans, dp[i + 1]);
                break;
            } else {
                v.push_back(j);
                vist[j] = true;
            }
        }

        if (has_empty) {
            ans = std::max(ans, dp[i + 1]);
        }
    }
    std::cout << ans << '\n';

    for (int i = 1; i <= n; ++i) {
        for (int j : a[i]) {
            last_pos[j] = 0;
        }
    }
    clear();
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }
}