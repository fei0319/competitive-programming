#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 4e5 + 19;

char str[maxn];
int n, a[maxn];
int s[2][maxn], t[2];
int cnt[2], pnt[2], qnt[2];

void solve(void) {
    std::cin >> n;
    cnt[0] = cnt[1] = pnt[0] = pnt[1] = qnt[0] = qnt[1] = 0;
    t[0] = t[1] = 0;
    std::cin >> str + 1;
    for (int i = 1; i <= n + n; ++i) {
        a[i] = str[i] - '0';
        ++cnt[a[i]];
    }
    if (cnt[0] % 2 == 1) {
        std::cout << "-1" << std::endl;
        return;
    }
    std::vector<int> p, q, b;
    for (int i = 1; i <= n + n; ++i) {
        if (pnt[a[i]] < cnt[a[i]] / 2) {
            s[0][++t[0]] = i;
            ++pnt[a[i]];
        } else {
            s[1][++t[1]] = i;
            ++qnt[a[i]];
        }
    }
    bool pf = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[s[0][i]] != a[s[1][i]] && a[s[0][i]] == pf) {
            p.swap(q);
        }
        if (a[s[0][i]] != a[s[1][i]]) {
            pf = a[s[0][i]];
        }
        p.push_back(s[0][i]);
        q.push_back(s[1][i]);
    }
    for (int i = 0; i < n; ++i) {
        if (a[p[i]] != a[q[i]]) {
            b.push_back(p[i]);
        }
    }
    std::cout << b.size() << ' ';
    for (int i : b) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
    for (int i : p) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
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