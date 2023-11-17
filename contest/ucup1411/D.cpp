#include <iostream>
#include <vector>
#include <algorithm>

using ll = long long int;

const ll INF = 1e18;

template <typename T>
class Segment {
    struct Node {
        int minp;
        T min, tag;
    };
    int n;
    std::vector<Node> tr;
    void push_down(int node) {
        if (tr[node].tag == 0) {
            return;
        }
        tr[node << 1].min += tr[node].tag;
        tr[node << 1].tag += tr[node].tag;
        tr[node << 1 | 1].min += tr[node].tag;
        tr[node << 1 | 1].tag += tr[node].tag;
        tr[node].tag = 0;
    }
    void push_up(int node) {
        tr[node].min = std::min(tr[node << 1].min, tr[node << 1 | 1].min);
        if (tr[node << 1].min <= tr[node << 1 | 1].min) {
            tr[node].minp = tr[node << 1].minp;
        } else {
            tr[node].minp = tr[node << 1 | 1].minp;
        }
    }
    void build(int node, int L, int R, std::vector<T> &a) {
        tr[node].min = a[L];
        tr[node].tag = 0;
        tr[node].minp = L;
        if (L == R) {
            return;
        }
        int mid = (L + R) / 2;
        build(node << 1, L, mid, a);
        build(node << 1 | 1, mid + 1, R, a);
        push_up(node);
    }
    void add(int node, int L, int R, int l, int r, const T &val) {
        if (l <= L && R <= r) {
            tr[node].min += val;
            tr[node].tag += val;
            return;
        }
        int mid = (L + R) / 2;
        push_down(node);
        if (l <= mid) add(node << 1, L, mid, l, r, val);
        if (r > mid) add(node << 1 | 1, mid + 1, R, l, r, val);
        push_up(node);
    }
public:
    explicit Segment(std::vector<T> &a) {
        n = a.size();
        tr.resize(n * 4);
        build(1, 0, n - 1, a);
    }
    void add(int l, int r, const T &val) {
        add(1, 0, n - 1, l, r, val);
    }
    std::pair<T, int> min(int l, int r) {
        return {tr[1].min, tr[1].minp};
    }
};

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<ll> a(n);
    for (ll &i : a) {
        int x;
        std::cin >> x;
        i = x;
    }

    Segment<ll> mt {a};

    std::vector<std::pair<int, int>> voucher(m);
    for (auto &[r, w] : voucher) {
        std::cin >> r >> w;
        mt.add(0, r - 1, -w);
    }
    std::sort(voucher.begin(), voucher.end());

    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        auto [val, x] = mt.min(0, n - 1);
        mt.add(x, x, INF);
        ans += val;
        x += 1;

        while (!voucher.empty() && voucher.back().first >= x) {
            auto [r, w] = voucher.back();
            voucher.pop_back();
            mt.add(0, r - 1, w);
        }

        std::cout << ans << ' ';
    }
    std::cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
}
