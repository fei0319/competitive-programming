#include <bits/stdc++.h>

using ll = long long int;

int n;
std::string s;

void solve(void) {
    std::cin >> n >> s;
    int pos = -1;
    for (int i = 0; i + 1 < s.length(); ++i)
        if (s[i] != s[i + 1]) {
            pos = i;
            break;
        }
    if (pos == -1) {
        std::cout << "-1\n";
        return;
    }
    if (s[pos] == 'L')
        std::cout << pos + 1 << '\n';
    else
        std::cout << "0\n";
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