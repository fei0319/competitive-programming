#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 1e6 + 19;
const int MAXS = 1e6;

int n;

int fail[MAXS][26], cnt[MAXS], next[MAXS];
int tot;
int insert(const std::string_view &s) {
    int now = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (!fail[now][s[i] - 'a']) {
            fail[now][s[i] - 'a'] = ++tot;
        }
        now = fail[now][s[i] - 'a'];
    }
    return now;
}
void build() {
    static int q[MAXS], h, t;
    h = 1, t = 0;

    for (int i = 0; i < 26; ++i) {
        if (fail[0][i]) {
            q[++t] = fail[0][i];
        }
    }

    while (h <= t) {
        int node = q[h++];

        for (int i = 0; i < 26; ++i) {
            if (fail[node][i]) {
                next[fail[node][i]] = fail[next[node]][i];
                q[++t] = fail[node][i];
            } else {
                fail[node][i] = fail[next[node]][i];
            }
        }
    }
}

int ans[MAXN];
int deg[MAXS], q[MAXS], h, t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::string t;
        std::cin >> t;

        ans[i] = insert(t);
    }

    build();

    std::string s;
    std::cin >> s;
    int now = 0;
    for (int i = 0; i < s.size(); ++i) {
        now = fail[now][s[i] - 'a'];
        cnt[now] += 1;
    }

    for (int i = 1; i <= tot; ++i) {
        ++deg[next[i]];
    }
    h = 1, t = 0;
    for (int i = 1; i <= tot; ++i) {
        if (deg[i] == 0) {
            q[++t] = i;
        }
    }
    while (h <= t) {
        int node = q[h++];
        --deg[next[node]];
        cnt[next[node]] += cnt[node];
        if (deg[next[node]] == 0) {
            q[++t] = next[node];
        }
    }

    for (int i = 1; i <= n; ++i) {
        std::cout << cnt[ans[i]] << '\n';
    }

    return 0;
}