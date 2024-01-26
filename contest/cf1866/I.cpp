#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 2e5 + 19;

int n, m, k;
std::vector<int> a[MAXN];

struct BIT {
    int tr[MAXN];
    void update(int x, int k) {
        for (; x <= m; x += x & -x) {
            tr[x] += k;
        }
    }
    int query(int x) const {
        int res = 0;
        for (; x; x -= x & -x) {
            res += tr[x];
        }
        return res;
    }
    int operator[](int index) const {
        return query(index) - query(index - 1);
    }
} mt;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m >> k;
    for (int i = 0; i < k; ++i) {
        int x, y;
        std::cin >> x >> y;
        a[n - x + 1].push_back(m - y + 1);
    }

    for (int i = 1; i <= n; ++i) {
        a[i].push_back(m + 1);
        std::sort(a[i].begin(), a[i].end());
    }

    bool ans = false;
    for (int i = 1; i <= n; ++i) {
        for (int j : a[i]) {
            if (!mt[j]) {
                mt.update(j, 1);
            }
        }
        int l = 1, r = a[i].front();
        while (l < r) {
            int mid = (l + r) / 2;
            if (mt.query(mid) == mid) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        if (l != a[i].front() && !mt[l]) {
            mt.update(l, 1);
            if (i == n && l == m) ans = true;
        }
    }

    std::cout << (ans ? "Bhinneka" : "Chaneka") << '\n';

    return 0;
}