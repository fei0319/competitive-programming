#include <bits/stdc++.h>

template <>
struct std::hash<std::vector<int>> {
    size_t operator()(const std::vector<int> &a) const {
        size_t res = 0;
        for (int i = 0; i < a.size(); ++i) {
            res ^= std::hash<int>()(a[i] + i * 4);
        }
        return res;
    }
};

using ll = long long int;

const int INF = 1e9;
const int MAXN = 1e5 + 19;

class Segment {
    static struct Node {
        int ls, rs;
        std::pair<int, int> min{INF, 0};
    } tr[MAXN * 2];
    static int tot;
    static void push_up(int node) {
        tr[node].min = std::min(tr[tr[node].ls].min, tr[tr[node].rs].min);
    }

public:
    static int rt;
    static int query() {
        return tr[rt].min.second;
    }
    static void modify(int &node, int L, int R, int x, const int &val) {
        if (!node) {
            node = ++tot;
            tr[node].min = {0, 0};
        }
        if (L == R) {
            tr[node].min.first += val;
            tr[node].min.second = L;
            return;
        }
        int mid = (L + R) / 2;
        if (x <= mid) {
            modify(tr[node].ls, L, mid, x, val);
        } else {
            modify(tr[node].rs, mid + 1, R, x, val);
        }
        push_up(node);
    }
};

using sg = Segment;
sg::Node sg::tr[MAXN * 2];
int sg::tot = 0;
int sg::rt = 0;

int n, m;

std::unordered_map<int, int> G[MAXN];
std::unordered_map<std::vector<int>, ll> value;
std::unordered_map<std::vector<int>, std::pair<ll, ll>> value_super;

void insert(std::pair<ll, ll> &p, ll x) {
    if (x > p.first) {
        p.second = p.first;
        p.first = x;
    } else if (x > p.second) {
        p.second = x;
    }
}

bool vist[MAXN];

int query() {
    return sg::query();
}
void modify(int x, const int &val) {
    sg::modify(sg::rt, 1, n, x, val);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        int x, y;
        std::cin >> x >> y;
    }
    for (int i = 1; i <= m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        G[u][v] = w;
        G[v][u] = w;
        modify(u, 1);
        modify(v, 1);
    }

    ll ans = 0;
    auto check = [&](std::vector<int> &a) {
        ll sum = 0;
        int missing_edges = a.size() * (a.size() - 1) / 2;
        for (int i = 0; i < a.size(); ++i) {
            int x = a[i];
            for (int j = i + 1; j < a.size(); ++j) {
                int y = a[j];
                if (G[x].contains(y)) {
                    sum += G[x][y];
                    missing_edges -= 1;
                }
            }
        }

        ans = std::max(ans, sum - missing_edges * missing_edges * ll(1e6));
        if (missing_edges == 0) {
            std::sort(a.begin(), a.end());
            value[a] = sum;

            for (int i = 0; i < a.size(); ++i) {
                std::vector<int> b;

                for (int j = 0; j < a.size(); ++j) {
                    if (i != j) {
                        b.push_back(a[j]);
                    }
                }

                insert(value_super[b], sum);
            }
        }
    };

    for (int i = 1; i <= n; ++i) {
        int x = query();

        vist[x] = true;
        std::vector<int> neighbors;
        for (auto [to, w] : G[x]) {
            if (!vist[to]) {
                neighbors.push_back(to);
            }
        }

        modify(x, INF);
        for (auto [to, w] : G[x]) {
            modify(to, -1);
        }

        int d = neighbors.size();
        for (int S = 1; S < (1 << d); ++S) {
            std::vector<int> a{x};
            for (int j = 0; j < d; ++j) {
                if (S & (1 << j)) {
                    a.push_back(neighbors[j]);
                }
            }
            check(a);
        }
    }

    for (auto &[a, p] : value_super) {
        ll res = p.first + p.second - value[a] - ll(1e6);
        ans = std::max(ans, res);
    }

    std::cout << ans << '\n';

    return 0;
}