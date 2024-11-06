#include <bits/stdc++.h>

using ll = long long int;

struct Node {
    int ls{0}, rs{0};
};

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::pair<int, int>> g(m);
    for (auto &[u, v] : g) {
        std::cin >> u >> v;
        u -= 1, v -= 1;
    }

    std::vector<std::vector<int>> G;

    int rt = 0, tot = 0;
    std::vector<Node> tr(n * 2 + 10);
    std::function<void(int &, int, int)> build = [&](int &node, int L,
                                                     int R) {
        if (!node) {
            node = ++tot;
            tr.push_back(Node{});
        }
        if (L == R) return;
        int mid = (L + R) / 2;
        build(tr[node].ls, L, mid);
        build(tr[node].rs, mid + 1, R);
    };
    build(rt, 0, n - 1);

    std::function<void(int, int, int)> init = [&](int node, int L, int R) {
        if (L == R) return;

        auto [ls, rs] = tr[node];
        if (ls) {
            G[node].push_back(ls);
            G[ls + tot].push_back(node + tot);
        }
        if (rs) {
            G[node].push_back(rs);
            G[rs + tot].push_back(node + tot);
        }

        int mid = (L + R) / 2;
        init(tr[node].ls, L, mid);
        init(tr[node].rs, mid + 1, R);
    };
    std::function<int(int)> get_id = [&](int x) {
        int L = 0, R = n - 1, node = 1;
        while (L < R) {
            int mid = (L + R) / 2;
            if (x <= mid) {
                node = tr[node].ls;
                R = mid;
            } else {
                node = tr[node].rs;
                L = mid + 1;
            }
        }
        return node;
    };
    std::function<void(int, int, int, int, int, int)> add =
        [&](int node, int L, int R, int l, int r, int x) {
            if (l <= L && R <= r) {
                G[x + tot].push_back(node);
                G[node + tot].push_back(x);
                return;
            }
            int mid = (L + R) / 2;
            if (l <= mid) add(tr[node].ls, L, mid, l, r, x);
            if (r > mid) add(tr[node].rs, mid + 1, R, l, r, x);
        };
    std::function<void(int)> construct = [&](int diff) {
        G.resize(tot * 2 + 1);
        for (auto &i : G) i.clear();

        init(1, 0, n - 1);

        for (auto [u, v] : g) {
            u = get_id(u), v = get_id(v);
            G[u].push_back(v + tot);
            G[v].push_back(u + tot);
        }

        for (int i = 0; i < n; ++i) {
            int l, r;
            l = std::max(i - diff + 1, 0), r = i - 1;
            if (l <= r) add(1, 0, n - 1, l, r, get_id(i));
            l = i + 1, r = std::min(i + diff - 1, n - 1);
            if (l <= r) add(1, 0, n - 1, l, r, get_id(i));
        }
    };

    int ind, cnt;
    std::vector<int> dfn(tot * 2 + 1), low(tot * 2 + 1), vist(tot * 2 + 1);
    std::vector<int> scc(tot * 2 + 1);
    std::vector<int> st;
    std::function<void(int)> dfs = [&](int node) {
        st.push_back(node);
        vist[node] = true;

        dfn[node] = low[node] = ++ind;
        for (int to : G[node]) {
            if (!dfn[to]) dfs(to);
            if (vist[to]) low[node] = std::min(low[node], low[to]);
        }

        if (dfn[node] == low[node]) {
            ++cnt;
            while (!st.empty() && dfn[st.back()] >= dfn[node]) {
                scc[st.back()] = cnt;
                vist[st.back()] = false;
                st.pop_back();
            }
        }
    };
    std::function<bool()> check = [&]() {
        for (int i = 1; i <= tot * 2; ++i) {
            dfn[i] = low[i] = 0;
        }
        ind = 0, cnt = 0;

        for (int i = 1; i <= tot * 2; ++i) {
            if (!dfn[i]) {
                dfs(i);
            }
        }

        for (int i = 1; i <= tot; ++i) {
            if (scc[i] == scc[i + tot]) {
                return false;
            }
        }
        return true;
    };

    int l = 1, r = n;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        construct(mid);
        if (check()) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    std::cout << l << '\n';
}

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}