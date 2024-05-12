#include <bits/stdc++.h>

using ll = long long int;

void read(auto &t) {
    std::string s;
    std::cin >> s;
    t.resize(s.size());
    for (int i = 0; i < (int)s.size(); ++i) {
        t[i] = (s[i] == '1');
    }
}

void solve() {
    int n, k;
    std::vector<int> s;
    std::cin >> n;
    n *= 2;
    read(s);

    if (s[0] == 0) {
        k = 2;
    } else {
        k = 3;
        for (int i = 1; i < n; i += 2) {
            s[i] ^= 1;
        }
    }
    for (int i = 1; i < n; ++i) {
        s[i] ^= s[i - 1];
    }

    if (s[n - 1] != (n / 2 * k) % 2 || s[n - 2] != s[n - 1]) {
        std::cout << "-1\n";
        return;
    }

    std::vector<int> a(n);
    for (int i = 0; i < n - 2; i += 2) {
        int v = k * (i / 2 + 1);
        a[i] = (s[i] % 2 == v % 2) ? v : v + 1;
        a[i + 1] = (s[i + 1] % 2 == v % 2) ? v + 2 : v + 1;
    }
    a[n - 1] = a[n - 2] = n / 2 * k;

    for (int i = n - 1; i >= 1; --i)
        a[i] -= a[i - 1];

    std::vector<std::vector<int>> ans(k);
    std::vector<int> sum(k);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < a[i]; ++j) {
            int x = -1;
            for (int p = 0; p < k; ++p) {
                if (ans[p].size() == i && (x == -1 || sum[p] < sum[x])) {
                    x = p;
                }
            }
            ans[x].push_back(1);
            sum[x] += 1;
        }
        for (int p = 0; p < k; ++p) {
            if (ans[p].size() == i) {
                ans[p].push_back(0);
            }
        }
    }

    std::cout << k << '\n';
    for (const auto &v : ans) {
        for (int i : v) {
            std::cout << (i ? '(' : ')');
        }
        std::cout << '\n';
    }
}

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}