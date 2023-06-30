#include <algorithm>
#include <cstdio>

constexpr int MAXN = 1e5 + 19;

int n, m, min_length;
std::pair<int, int> max, min, p[MAXN];

void solve() {
    std::scanf("%d%d", &n, &m);
    min_length = m;
    min = {m + 1, m + 1}, max = {0, 0};

    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &p[i].first, &p[i].second);
        min_length = std::min(min_length, p[i].second - p[i].first + 1);
        if (p[i].first > max.first ||
            (p[i].first == max.first && p[i].second < max.second))
            max = p[i];
        if (p[i].second < min.second ||
            (p[i].second == min.second && p[i].first > min.first))
            min = p[i];
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        int min_other = min_length;
        if (max.first > p[i].second || min.second < p[i].first)
            min_other = 0;
        else
            min_other =
                std::min(min_other, std::min(p[i].second - max.first + 1,
                                             min.second - p[i].first + 1));
        ans = std::max(ans, p[i].second - p[i].first + 1 - min_other);
    }
    printf("%d\n", ans * 2);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--)
        solve();
}