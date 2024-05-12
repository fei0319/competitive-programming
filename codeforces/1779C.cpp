#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e5 + 19;

int count(std::vector<int> a) {
    int n = a.size(), ans = 0;
    std::priority_queue<int> q;
    ll s = 0;
    for (int i : a) {
        //	std::cout << i << ' ';
        s += i;
        q.push(-i * 2);
        while (s < 0) {
            ++ans;
            s += q.top();
            q.pop();
        }
    }
    return ans;
}

int n, m, a[maxn];

void solve(void) {
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];

    std::vector<int> b, c;
    for (int i = m + 1; i <= n; ++i)
        b.push_back(a[i]);
    for (int i = m; i >= 2; --i)
        c.push_back(-a[i]);

    std::cout << count(b) + count(c) << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}