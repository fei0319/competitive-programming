#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e5 + 19;

bool vist[maxn];
int n, k, x;

void solve(void) {
    std::cin >> n >> k >> x;

    int sum = 0;
    if (n >= 12) {
        for (int i = n; i % 4 != 3; --i) {
            sum ^= i;
        }
    } else {
        for (int i = 1; i <= n; ++i) {
            sum ^= i;
        }
    }

    if (k % 2 == 0 && sum != 0) {
        std::cout << "NO\n";
        return;
    }
    if (k % 2 == 1 && sum != x) {
        std::cout << "NO\n";
        return;
    }

    for (int i = 1; i <= n; ++i) {
        vist[i] = 0;
    }

    std::vector<std::vector<int>> ans;
    for (int i = 1; i <= n; ++i) {
        if (vist[i]) continue;
        if (i == x) {
            vist[i] = 1;
            ans.emplace_back(std::vector<int>{i});
        } else if ((i ^ x) <= n) {
            vist[i] = 1;
            vist[i ^ x] = 1;
            ans.emplace_back(std::vector<int>{i, i ^ x});
        }
    }

    std::vector<int> rest;
    for (int i = 1; i <= n; ++i)
        if (!vist[i]) rest.push_back(i);
    if (!rest.empty()) ans.push_back(rest);

    if (ans.size() < k) {
        std::cout << "NO\n";
        return;
    }

    std::cout << "YES\n";

    std::vector<int> tail;
    while (ans.size() > k - 1) {
        for (int i : ans.back()) tail.push_back(i);
        ans.pop_back();
    }
    ans.push_back(tail);

    for (auto i : ans) {
        std::sort(i.begin(), i.end());
        std::cout << i.size();
        for (int j : i) std::cout << ' ' << j;
        std::cout << '\n';
    }
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