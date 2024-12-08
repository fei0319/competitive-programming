#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e7 + 19, maxm = 1e6 + 19;

bool vist[maxn];

struct Edge {
    int to, next;
} edge[maxn * 5];
int head[maxn], cnt;
void add(int from, int to) {
    edge[++cnt].to = to;
    edge[cnt].next = head[from];
    head[from] = cnt;
}

int x[maxm], y[maxm];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;
    for (int i = 1; i <= T; ++i) {
        std::cin >> x[i] >> y[i];
        vist[y[i] - x[i]] = 1;
    }

    constexpr int N = 1e7;
    for (int i = 2; i <= N; ++i)
        for (int j = i; j <= N; j += i)
            if (vist[j]) add(j, i);

    for (int i = 1; i <= T; ++i) {
        if (x[i] == y[i] - 1) {
            std::cout << "-1\n";
            continue;
        }
        int ans = 1e9;
        for (int j = head[y[i] - x[i]]; j; j = edge[j].next) {
            int v = edge[j].to;
            if (x[i] % v == 0) {
                ans = 0;
                break;
            }
            ans = std::min(ans, v - x[i] % v);
        }
        std::cout << ans << '\n';
    }

    return 0;
}