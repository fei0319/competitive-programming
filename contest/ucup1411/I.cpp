#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

using ll = long long int;

const int MAXS = 1e7;

class MergeableSegment {
    struct Node {
        int ls {0}, rs {0};
        int cnt {0};
        Node() = default;
    };
    Node *tr {new Node[MAXS]};
    int tot {0};
    ll k;
    void push_up(int node) {
        tr[node].cnt = tr[tr[node].ls].cnt + tr[tr[node].rs].cnt;
    }
    void insert(int &node, ll L, ll R, ll val) {
        if (!node) {
            node = ++tot;
        }
        tr[node].cnt += 1;
        if (L == R) {
            return;
        }
        ll mid = (L + R) / 2;
        if (val <= mid) {
            insert(tr[node].ls, L, mid, val);
        } else {
            insert(tr[node].rs, mid + 1, R, val);
        }
    }
    int merge(int x, int y, ll L, ll R) {
        if (!x || !y) {
            return x | y;
        }
        if (L == R) {
            tr[x].cnt += tr[y].cnt;
            return x;
        }
        ll mid = (L + R) / 2;
        tr[x].ls = merge(tr[x].ls, tr[y].ls, L, mid);
        tr[x].rs = merge(tr[x].rs, tr[y].rs, mid + 1, R);
        push_up(x);
        return x;
    }
    ll query(int node, ll L, ll R, int rank) {
        if (L == R) {
            return L;
        }
        ll mid = (L + R) / 2;
        if (rank <= tr[tr[node].ls].cnt) {
            return query(tr[node].ls, L, mid, rank);
        } else {
            return query(tr[node].rs, mid + 1, R, rank - tr[tr[node].ls].cnt);
        }
    }
    std::pair<int, int> split(int node, ll L, ll R, int d) {
        if (d == 0) {
            return {0, node};
        } else if (d == tr[node].cnt) {
            return {node, 0};
        }
        int x = node, y = ++tot;
        if (L == R) {
            tr[y].cnt = tr[node].cnt - d;
            tr[x].cnt = d;
            return {x, y};
        }
        ll mid = (L + R) / 2;
        if (d <= tr[tr[node].ls].cnt) {
            auto [a, b] = split(tr[node].ls, L, mid, d);
            tr[x].ls = a, tr[y].ls = b;
            tr[y].rs = tr[x].rs, tr[x].rs = 0;
        } else {
            auto [a, b] = split(tr[node].rs, mid + 1, R, d - tr[tr[node].ls].cnt);
            tr[x].rs = a, tr[y].rs = b;
        }
        push_up(x), push_up(y);
        return {x, y};
    }
public:
    explicit MergeableSegment(ll k) : k(k) {
    }
    ~MergeableSegment() {
        delete[] tr;
    }
    void insert(int &node, ll val) {
        insert(node, 0, k - 1, val);
    }
    std::size_t size(int node) {
        return tr[node].cnt;
    }
    int merge(int x, int y) {
        return merge(x, y, 0, k - 1);
    }
    ll query(int node, int rank) {
        return query(node, 0, k - 1, rank);
    }
    std::pair<int, int> split(int node, int x) {
        return split(node, 0, k - 1, x);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    ll k;
    std::cin >> n >> m >> k;

    std::vector<ll> a(n);
    for (auto &i : a) {
        std::cin >> i;
    }
    std::sort(a.begin(), a.end());

    std::vector<std::vector<ll>> b;
    for (auto i : a) {
        if (!b.empty() && i / k == b.back().back() / k) {
            b.back().push_back(i);
        } else {
            b.push_back(std::vector<ll> {i});
        }
    }

    MergeableSegment mt {k};
    ll tag {0};
    std::vector<std::pair<ll, int>> tree;
    for (auto &vec : b) {
        int rt = 0;
        for (ll i : vec) {
            mt.insert(rt, i % k);
        }
        tree.emplace_back(vec[0] / k, rt);
    }

    auto change = [&tag, &tree, &mt](ll x) {
        tag += x;
        while (tree.size() > 1) {
            auto &[d0, rt0] = tree[tree.size() - 2];
            auto &[d1, rt1] = tree[tree.size() - 1];
            if (tag >= (d1 - d0) * mt.size(rt1)) {
                tag -= (d1 - d0) * mt.size(rt1);
                rt0 = mt.merge(rt0, rt1);
                tree.pop_back();
            } else {
                break;
            }
        }
        auto &[d, rt] = tree.back();
        d -= tag / mt.size(rt), tag %= mt.size(rt);
    };
    auto query = [&tree, &mt, &tag, &k, &a](int x) {
        if (tree.size() == 1 || tree[tree.size() - 2].first != tree[tree.size() - 1].first - 1) {
            auto [d, rt] = tree.back();
            int sz = mt.size(rt);
            if (x > sz) {
                return a[a.size() - x];
            } else if (x <= sz - tag) {
                return mt.query(rt, sz - tag - x + 1) + d * k;
            } else {
                return mt.query(rt, sz - (x - sz + tag) + 1) + (d - 1) * k;
            }
        } else {
            auto &[d0, rt0] = tree[tree.size() - 2];
            auto &[d1, rt1] = tree[tree.size() - 1];

            if (tag) {
                auto [p, q] = mt.split(rt1, mt.size(rt1) - tag);
                rt0 = mt.merge(rt0, q), rt1 = p;
                tag = 0;
            }

            int sz0 = mt.size(rt0), sz1 = mt.size(rt1);
            if (x <= sz1) {
                return mt.query(rt1, sz1 - x + 1) + d1 * k;
            } else if (x <= sz1 + sz0) {
                return mt.query(rt0, sz0 - (x - sz1) + 1) + d0 * k;
            } else {
                return a[a.size() - x];
            }
        }
    };

    while (m--) {
        std::string op;
        ll x;
        std::cin >> op >> x;
        if (op == "C") {
            change(x);
        } else {
            std::cout << query(x) << '\n';
        }
    }
}