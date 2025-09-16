#include <bits/stdc++.h>

template <typename T, size_t S, size_t A = sizeof(T)>
class Rc {
    struct Block {
        std::byte data[A];
        int ref;
    };
    static int head;
    static Block pool[S];
    static int alloc() {
        int x = head;
        head += pool[head].ref + 1;
        new (pool + head) T();
        return x;
    }
    static void free(int idx) {
        int x = head;
        pool[idx].ref = head - idx - 1;
        head = idx;
        reinterpret_cast<T *>(pool + x)->~T();
    }

    int idx{};
    void release(int idx) {
        if (idx) {
            if (--pool[idx].ref == 0) {
                free(idx);
            }
        }
    }
    explicit Rc(int x) : idx(x) {}

public:
    Rc() = default;
    Rc(const Rc &other) {
        idx = other.idx;
        if (idx) pool[idx].ref += 1;
    }
    Rc(Rc &&other) {
        idx = other.idx;
        if (idx) other.idx = 0;
    }
    ~Rc() { release(idx); }
    Rc &operator=(const Rc &other) {
        if (this != &other) {
            release(idx);
            idx = other.idx;
            if (idx) pool[idx].ref += 1;
        }
        return *this;
    }
    Rc &operator=(Rc &&other) {
        if (this != &other) {
            release(idx);
            idx = other.idx;
            if (idx) other.idx = 0;
        }
        return *this;
    }
    static Rc create() {
        int idx = alloc();
        pool[idx].ref = 1;
        return Rc{idx};
    }

    T &operator*() const { return *reinterpret_cast<T *>(pool + idx); }
    T *operator->() const { return reinterpret_cast<T *>(pool + idx); }
    explicit operator bool() const { return idx; }
};
template <typename T, size_t S, size_t A>
constinit int Rc<T, S, A>::head = 1;
template <typename T, size_t S, size_t A>
constinit Rc<T, S, A>::Block Rc<T, S, A>::pool[S];

using i64 = int64_t;
constexpr int S = 5e6;
struct Node {
    Rc<Node, S, 12> ls, rs;
    int sum;
};
using NodeRc = Rc<Node, S, 12>;

NodeRc copy(const NodeRc &x) {
    auto new_x = NodeRc::create();
    *new_x = *x;
    return new_x;
}
NodeRc push_up(const NodeRc &ls, const NodeRc &rs) {
    auto x = NodeRc::create();
    x->ls = ls;
    x->rs = rs;
    x->sum = ls->sum + rs->sum;
    return x;
}

NodeRc modify(const NodeRc &x, int L, int R, int h) {
    if (L == R) {
        auto t = copy(x);
        t->sum += 1;
        return t;
    }
    const int mid = (L + R) / 2;
    if (h <= mid) return push_up(modify(x->ls, L, mid, h), x->rs);
    else return push_up(x->ls, modify(x->rs, mid + 1, R, h));
}
NodeRc merge(const NodeRc &x, const NodeRc &y, int L, int R) {
    if (!x) return y;
    if (!y) return x;
    if (L == R) {
        auto t = NodeRc::create();
        t->ls = NodeRc{};
        t->rs = NodeRc{};
        t->sum = x->sum + y->sum;
        return t;
    }
    const int mid = (L + R) / 2;
    return push_up(merge(x->ls, y->ls, L, mid),
                   merge(x->rs, y->rs, mid + 1, R));
}
int query(const NodeRc &x, int L, int R, int k) {
    if (L == R) {
        if (k <= x->sum) return L;
        return -1;
    }
    const int mid = (L + R) / 2;
    if (k <= x->rs->sum) return query(x->rs, mid + 1, R, k);
    return query(x->ls, L, mid, k - x->rs->sum);
}

struct DSU {
    std::vector<int> fa;
    explicit DSU(int n) : fa(n) { std::iota(fa.begin(), fa.end(), 0); }
    int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<int> h(n);
    for (int i = 0; i < n; ++i) std::cin >> h[i];

    std::vector<int> vals(h);
    std::ranges::sort(vals);
    vals.resize(std::unique(vals.begin(), vals.end()) - vals.begin());
    for (int &h : h) h = std::ranges::lower_bound(vals, h) - vals.begin();

    struct Edge {
        int u, v, w;
    };
    std::vector<Edge> edge_list(m);
    for (auto &[u, v, w] : edge_list) {
        std::cin >> u >> v >> w;
        --u, --v;
    }
    std::ranges::sort(edge_list,
                      [](auto e1, auto e2) { return e1.w < e2.w; });

    const int min_h = std::ranges::min(h);
    const int max_h = std::ranges::max(h);
    std::vector<NodeRc> rt(n);
    for (int i = 0; i < n; ++i) rt[i] = modify(rt[i], min_h, max_h, h[i]);

    struct Query {
        int v, x, k, id;
    };
    std::vector<Query> query_list(q);
    for (int i = 0; i < q; ++i) {
        auto &[v, x, k, id] = query_list[i];
        std::cin >> v >> x >> k;
        --v;
        id = i;
    }
    std::ranges::sort(query_list,
                      [](auto q1, auto q2) { return q1.x < q2.x; });

    int j = 0;
    DSU dsu(n);
    std::vector<int> ans(q);
    for (const auto &[v, x, k, id] : query_list) {
        while (j < edge_list.size() && edge_list[j].w <= x) {
            const auto [u, v, w] = edge_list[j++];
            const int fu = dsu.find(u);
            const int fv = dsu.find(v);
            if (fu != fv) {
                rt[fu] = merge(rt[fu], rt[fv], min_h, max_h);
                dsu.fa[fv] = fu;
            }
        }

        ans[id] = query(rt[dsu.find(v)], min_h, max_h, k);
        if (ans[id] != -1) ans[id] = vals[ans[id]];
    }

    std::copy(ans.begin(), ans.end(),
              std::ostream_iterator<int>(std::cout, "\n"));
}
