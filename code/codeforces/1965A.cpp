#include <bits/stdc++.h>

using ll = long long int;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int &i : a) {
        std::cin >> i;
    }

    std::sort(a.begin(), a.end());
    std::vector<int> b;
    for (int i = 0; i < n; ++i) {
        int v = a[i];
        if (i >= 1)
            v -= a[i - 1];
        if (v != 0)
            b.push_back(v);
    }

    bool is_alice = true;
    std::reverse(b.begin(), b.end());
    while (!b.empty() && b.back() == 1) {
        b.pop_back();
        is_alice ^= 1;
    }

    if (!b.empty()) {
        is_alice ^= 1;
    }
    std::cout << (is_alice ? "Bob\n" : "Alice\n");
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