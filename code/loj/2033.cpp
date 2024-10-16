#include <bits/stdc++.h>

using i64 = int64_t;
i64 ans;

template <typename T>
struct SuffixAutomaton {
    std::vector<int> len, link;
    std::vector<T> next;
    int tot;
    explicit SuffixAutomaton(int size)
        : len(size), link(size), next(size), tot(1) {}
    void set(int &x, int y) {
        ans += len[x];
        x = y;
        ans -= len[x];
    }
    int extend(int p, int c) {
        int cur = ++tot;
        len[cur] = len[p] + 1;
        ans += len[cur];
        for (; p && !next[p][c]; p = link[p])
            next[p][c] = cur;
        int q = next[p][c];
        if (!p) {
            set(link[cur], 1);
        } else if (len[q] == len[p] + 1) {
            set(link[cur], q);
        } else {
            int r = ++tot;
            len[r] = len[p] + 1;
            ans += len[r];
            set(link[r], link[q]);
            next[r] = next[q];
            set(link[q], r);
            set(link[cur], r);
            for (; next[p][c] == q; p = link[p])
                next[p][c] = r;
        }
        return cur;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    SuffixAutomaton<std::map<int, int>> sam{n * 2 + 1};
    int p = 1;

    for (int i : a) {
        p = sam.extend(p, i);
        std::cout << ans << '\n';
    }
}
