#include <bits/stdc++.h>

using ll = long long int;

const int MAXS = 4e3 + 19;
const int SIGMA = 12;
const int INF = 1e9;

struct Node {
    int fail[SIGMA], next;
    int val;
} tr[MAXS];
int tot;

void insert(const std::string_view &s, int value) {
    int now = 0;
    for (char c : s) {
        int &nxt = tr[now].fail[c - 'a'];
        if (!nxt) {
            nxt = ++tot;
        }
        now = nxt;
    }
    tr[now].val += value;
}

void build() {
    static int q[MAXS], h, t;
    h = 1, t = 0;
    for (int i = 0; i < SIGMA; ++i) {
        if (tr[0].fail[i]) {
            q[++t] = tr[0].fail[i];
        }
    }

    while (h <= t) {
        int node = q[h++];
        tr[node].val += tr[tr[node].next].val;
        for (int i = 0; i < SIGMA; ++i) {
            if (tr[node].fail[i]) {
                q[++t] = tr[node].fail[i];
                tr[tr[node].fail[i]].next = tr[tr[node].next].fail[i];
            } else {
                tr[node].fail[i] = tr[tr[node].next].fail[i];
            }
        }
    }
}

int dp[MAXS][1 << SIGMA];
std::pair<int, char> from[MAXS][1 << SIGMA];

void add_value(int node, int status, int value, int f, char c) {
    if (value > dp[node][status]) {
        dp[node][status] = value;
        from[node][status] = {f, c};
    }
}

std::string construct_from(const std::string_view &s) {
    std::string res;
    int S = 0, now = -1;

    for (char c : s) {
        if (now - 1 >= 0 && res[now - 1] == c) {
            now -= 1;
        } else if (now + 1 < res.size() && res[now + 1] == c) {
            now += 1;
        } else if (now + 1 >= res.size()) {
            if (S & (1 << (c - 'a'))) {
                return {};
            }
            now += 1;
            S |= 1 << (c - 'a');
            res.push_back(c);
        } else if (now - 1 < 0) {
            if (S & (1 << (c - 'a'))) {
                return {};
            }
            S |= 1 << (c - 'a');
            res = c + res;
        }
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int c;
        std::string s;
        std::cin >> c >> s;

        s = construct_from(s);
        if (!s.empty()) {
            insert(s, c);
            if (s.size() >= 2) {
                std::reverse(s.begin(), s.end());
                insert(s, c);
            }
        }
    }

    build();

    for (int i = 0; i <= tot; ++i) {
        for (int S = 0; S < (1 << SIGMA); ++S) {
            dp[i][S] = -INF;
        }
    }
    dp[0][0] = 0;
    for (int S = 0; S < (1 << SIGMA); ++S) {
        for (int node = 0; node <= tot; ++node) {
            int value = dp[node][S];
            for (int i = 0; i < SIGMA; ++i) {
                if (!(S & (1 << i))) {
                    add_value(tr[node].fail[i], S | (1 << i),
                              value + tr[tr[node].fail[i]].val, node, 'a' + i);
                }
            }
        }
    }

    int now = 0, S = (1 << SIGMA) - 1;
    for (int i = 1; i <= tot; ++i) {
        if (dp[i][(1 << SIGMA) - 1] > dp[now][(1 << SIGMA) - 1]) {
            now = i;
        }
    }

    while (S) {
        auto [nxt, c] = from[now][S];
        std::cout << c;

        now = nxt;
        S ^= 1 << (c - 'a');
    }

    return 0;
}