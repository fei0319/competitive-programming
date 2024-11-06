#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 1e6 + 19;

int n;
std::vector<int> G[MAXN];

int size[MAXN];
ll dp[MAXN], g[MAXN];

void dfs1(int node) {
    size[node] = 1;
    for (int to : G[node]) {
        size[node] += size[to];
        dp[node] += dp[to];
    }
    dp[node] += size[node];
}

ll ans;
void dfs2(int node) {
    for (int to : G[node]) {
        g[to] =
            dp[node] - (dp[to] + size[to]) + g[node] + (n - size[node]);
    }

    ll res = dp[node] - size[node] + g[node];
    std::vector<int> sz{n - size[node]};
    for (int to : G[node]) {
        sz.push_back(size[to]);
    }

    if (*std::max_element(sz.begin(), sz.end()) >= n / 2) {
        int max = *std::max_element(sz.begin(), sz.end());
        res += (ll)(max + 1) * (n - max);
    } else {

        std::vector<int> old_sz;
        old_sz.swap(sz);
        std::sort(old_sz.begin(), old_sz.end());
        for (int l = 0, r; l < old_sz.size(); l = r + 1) {
            r = l;
            while (r + 1 < old_sz.size() && old_sz[r] == old_sz[r + 1]) {
                r += 1;
            }
            int tot = r - l + 1, val = old_sz[l];
            for (int i = 0; i < 21; ++i) {
                if ((1 << i) <= tot) {
                    sz.push_back((1 << i) * val);
                    tot -= 1 << i;
                }
            }
            if (tot > 0) {
                sz.push_back(tot * val);
            }
        }

        std::bitset<MAXN> dp;
        dp.set(0);
        for (int i : sz) {
            dp |= dp << i;
        }
        int max = 0;
        for (int i = 1; i <= n; ++i) {
            if (dp.test(i)) {
                max = std::max(max, std::min(i, n - 1 - i));
            }
        }
        res += (ll)(max + 1) * (n - max);
    }
    ans = std::max(ans, res);
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

    for (int i = n; i >= 1; --i) {
        dfs1(i);
    }
    for (int i = 1; i <= n; ++i) {
        dfs2(i);
    }

    std::cout << ans << '\n';

    return 0;
}