#include <bits/stdc++.h>

using ll = long long int;

char query(int a, int b, int c, int d) {
    std::cout << "? " << a << ' ' << b << ' ' << c << ' ' << d << '\n';
    std::cout.flush();

    std::string s;
    std::cin >> s;
    return s[0];
}

void answer(int x, int y) {
    std::cout << "! " << x << ' ' << y << '\n';
    std::cout.flush();
}

void solve() {
    int n;
    std::cin >> n;

    int max = 0;
    for (int i = 1; i < n; ++i) {
        if (query(max, max, i, i) == '<') {
            max = i;
        }
    }

    int p = 0;
    std::vector<int> v{p};
    for (int i = 1; i < n; ++i) {
        char t = query(max, p, max, i);
        if (t == '<') {
            p = i;
            v = {i};
        } else if (t == '=') {
            v.push_back(i);
        }
    }

    int min = v[0];
    for (int i = 1; i < v.size(); ++i) {
        if (query(min, min, v[i], v[i]) == '>') {
            min = v[i];
        }
    }

    answer(max, min);
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