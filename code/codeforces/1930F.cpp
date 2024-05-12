#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 1e7 + 19, B = 24;
bool a[MAXN], b[MAXN];

int get(int v, bool *a) {
    int res = 0;
    for (int i = B; i >= 0; --i) {
        if ((v & (1 << i)) && a[res | (1 << i)]) {
            res |= (1 << i);
        }
    }
    return res;
}

void dfs(int x, bool *a) {
    if (a[x]) {
        return;
    }
    a[x] = true;
    for (int i = B; i >= 0; --i) {
        if (x & (1 << i)) {
            dfs(x ^ (1 << i), a);
        }
    }
}

void update(int v, bool *a) {
    dfs(v, a);
}

void solve() {
    int n, q;
    std::cin >> n >> q;

    int L = 1;
    while (L <= n)
        L *= 2;

    int lastans = 0;
    while (q--) {
        int v;
        std::cin >> v;
        v = (v + lastans) % n;

        lastans = std::max({lastans, get(v, b), get((L - 1) ^ v, a)});
        assert(lastans >= 0);
        update(v, a), update((L - 1) ^ v, b);
        std::cout << lastans << ' ';
    }
    std::cout << '\n';

    std::fill(a, a + L, false);
    std::fill(b, b + L, false);
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