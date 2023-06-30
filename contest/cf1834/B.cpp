#include <bits/stdc++.h>

int n;
char s[114], t[114];

void solve() {
    std::cin >> s >> t;
    n = std::max(strlen(s), strlen(t));
    std::reverse(s, s + strlen(s)), std::reverse(t, t + strlen(t));
    for (int i = strlen(s); i < n; ++i)
        s[i] = '0';
    for (int i = strlen(t); i < n; ++i)
        t[i] = '0';
    s[n] = t[n] = '\0';
    std::reverse(s, s + strlen(s)), std::reverse(t, t + strlen(t));

    int i = 0;
    while (i < n - 1 && s[i] == t[i])
        ++i;
    std::cout << abs((int)s[i] - (int)t[i]) + (n - i - 1) * 9 << '\n';
}

int main() {
    int t;
    std::cin >> t;
    while (t--)
        solve();
}