#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e6 + 19;

char s[maxn];
int a, b, c, d, n;

void solve(void) {
    std::cin >> a >> b >> c >> d >> (s + 1);
    n = a + b + (c + d) * 2;

    for (int i = 1; i <= n; ++i)
        if (s[i] == 'A') --a;
        else --b;
    if (-a != c + d || -b != c + d) {
        std::cout << "NO\n";
        return;
    }

    int common = 0;
    std::vector<int> a_only, b_only;
    for (int l = 1, r; l <= n; l = r + 1) {
        r = l;
        while (r + 1 <= n && s[r + 1] != s[r]) ++r;
        if ((r - l) % 2 == 0) common += (r - l) / 2;
        else {
            int num = (r - l + 1) / 2;
            if (s[l] == 'A') {
                a_only.push_back(num);
            } else {
                b_only.push_back(num);
            }
        }
    }

    std::sort(a_only.begin(), a_only.end()),
        std::sort(b_only.begin(), b_only.end());
    for (int num : a_only) {
        int sub = std::min(num, c);
        c -= sub, num -= sub;
        if (num > 1) common += num - 1;
    }
    for (int num : b_only) {
        int sub = std::min(num, d);
        d -= sub, num -= sub;
        if (num > 1) common += num - 1;
    }

    //	std::cout << c << ' ' << d << ' ' << common << '\n';
    if (common >= c + d) std::cout << "YES\n";
    else std::cout << "NO\n";
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