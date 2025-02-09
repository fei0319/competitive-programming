#include <bits/stdc++.h>

using ll = long long int;

int n, cnt[26], a[26];
std::string s;

int calc(int x) {
    int num = n / x, res = 0;
    for (int i = 0; cnt[a[i]] > x; ++i) res += cnt[a[i]] - x;
    for (int i = num; i < 26; ++i) res += cnt[a[i]];
    return res;
}

void output(int x) {
    int num = n / x;
    std::vector<int> v;
    static bool vist[26];
    for (int i = 0; i < 26; ++i) vist[i] = 0;
    for (int i = 0; i < num; ++i)
        if (cnt[a[i]] < x) v.push_back(a[i]), vist[a[i]] = 1;
    for (int i = 0; i < s.length(); ++i) {
        if (!vist[s[i] - 'a'] && cnt[s[i] - 'a'] != x &&
            cnt[s[i] - 'a'] != 0) {
            std::cout << char(v.back() + 'a');
            --cnt[s[i] - 'a'], ++cnt[v.back()];
            if (cnt[v.back()] == x) v.pop_back();
        } else
            std::cout << s[i];
    }
}

void solve(void) {
    std::cin >> n;
    std::cin >> s;
    for (int i = 0; i < 26; ++i) cnt[i] = 0, a[i] = i;
    for (int i = 0; i < s.length(); ++i) ++cnt[s[i] - 'a'];

    std::sort(a, a + 26,
              [](const int &x, const int &y) { return cnt[x] > cnt[y]; });

    int x = 0, ans = 1e9;
    for (int i = 1; i <= n; ++i) {
        if (n % i == 0 && n / i <= 26) {
            int v = calc(i);
            if (v < ans) ans = v, x = i;
        }
    }

    std::cout << ans << '\n';
    output(x);
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