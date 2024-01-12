#include <bits/stdc++.h>

using ll = long long int;

constexpr int MAXN = 4e6;
std::vector<std::vector<int>> tower;
std::vector<std::vector<ll>> dp, s;
std::pair<int, int> pos[MAXN];

int n;

void solve(void) {
    std::cin >> n;

    std::cout << dp[pos[n].first][pos[n].second] << '\n';
}

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    for (int i = 1, ind = 0; i <= 1450; ++i) {
        dp.push_back(std::vector<ll>(i));
        s.push_back(std::vector<ll>(i));
        std::vector<int> tmp;
        for (int j = 1; j <= i; ++j) {
            tmp.push_back(++ind);
            pos[ind] = std::make_pair(i - 1, j - 1);
            s[i - 1][j - 1] = (ll)ind * ind;
            if (i > 1 && j < i) {
                s[i - 1][j - 1] += s[i - 2][j - 1];
            }
            dp[i - 1][j - 1] = s[i - 1][j - 1];
            if (j > 1 && i > 1) {
                dp[i - 1][j - 1] += dp[i - 2][j - 2];
            }
        }
        tower.push_back(tmp);
    }

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}