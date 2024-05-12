#include <bits/stdc++.h>

using ld = long double;
using ll = long long int;

constexpr int MAXN = 1e5 + 19, S = 32;

int n, a[MAXN];
char c[MAXN];

struct Node {
    int l, r;
    ld value;
};

void mul_add(int L, int R) {
    if (L > R) {
        return;
    }

    for (int i = L; i < R; ++i) {
        c[i] = '+';
    }

    std::vector<Node> p;
    for (int l = L, r; l <= R; l = r + 1) {
        r = l;
        if (a[l] > 1) {
            while (r < R && a[r + 1] > 1) {
                ++r;
            }
            ld value = 1;
            for (int i = l; i < r; ++i) {
                c[i] = '*';
            }
            for (int i = l; i <= r; ++i) {
                value *= a[i];
            }
            p.push_back(Node{l, r, value});
        }
    }

    if (p.empty()) {
        return;
    }

    ld mul = 1;
    for (auto node : p) {
        mul *= node.value;
    }
    if (mul >= 1e18) {
        for (int i = p.front().l; i < p.back().r; ++i) {
            c[i] = '*';
        }
        return;
    }

    std::vector<ld> dp(p.size());
    std::vector<int> from(p.size());

    dp[0] = p[0].value + p[0].l - 1;
    from[0] = -1;
    for (int i = 1; i < p.size(); ++i) {

        ld now = 1;
        for (int j = i; j >= 0; --j) {
            now *= p[j].value;
            ld v = (j - 1 >= 0 ? dp[j - 1] : ld(0)) + now;
            if (j - 1 >= 0) {
                v += p[j].l - p[j - 1].r - 1;
            } else {
                v += p[j].l - 1;
            }
            if (v > dp[i]) {
                dp[i] = v;
                from[i] = j - 1;
            }
        }
    }

    int now = p.size() - 1;
    while (now != -1) {
        int f = from[now];

        for (int i = p[f + 1].l; i < p[now].r; ++i) {
            c[i] = '*';
        }

        now = f;
    }
}

void mul_add() {
    std::vector<int> p{0};
    for (int i = 1; i <= n; ++i) {
        if (a[i] == 0) {
            p.push_back(i);
        }
    }
    p.push_back(n + 1);
    for (int i = 0; i + 1 < p.size(); ++i) {
        mul_add(p[i] + 1, p[i + 1] - 1);
        c[p[i]] = '+';
        c[p[i + 1] - 1] = '+';
    }
}

void mul_sub() {
    if (std::any_of(a + 1, a + 1 + n, [](int x) {
            return x == 0;
        })) {
        int zero = std::find(a + 1, a + 1 + n, 0) - a;
        for (int i = 1; i + 1 < zero; ++i) {
            c[i] = '*';
        }
        c[zero - 1] = '-';
        for (int i = zero; i < n; ++i) {
            c[i] = '*';
        }
    } else {
        for (int i = 1; i < n; ++i) {
            c[i] = '*';
        }
    }
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }

    std::string str;
    std::cin >> str;

    std::set<char> s{str.begin(), str.end()};

    if (s.size() == 1) {
        for (int i = 1; i < n; ++i) {
            std::cout << a[i] << str;
        }
        std::cout << a[n];
        return 0;
    }

    if (s.contains('*')) {
        if (s.contains('+')) {
            mul_add();
        } else {
            mul_sub();
        }
        for (int i = 1; i < n; ++i) {
            std::cout << a[i] << c[i];
        }
        std::cout << a[n];
    } else {
        for (int i = 1; i < n; ++i) {
            std::cout << a[i] << '+';
        }
        std::cout << a[n];
    }
}