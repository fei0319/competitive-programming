#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 2e5 + 19;

int n, a[MAXN];
ll m;

struct Node {
    int len, x;
    ll value() const {
        int t = x + 1, b = len / t, f = len % t;

        return (ll)f * (b + 1) * (b + 1) + ll(t - f) * b * b;
    }
    ll benefit() const {
        return value() - Node{len, x + 1}.value();
    }
    bool operator<(const Node &b) const {
        return benefit() < b.benefit();
    }
} node[MAXN];

int get(int len, ll b) {
    int l = 0, r = len;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (Node{len, mid - 1}.benefit() >= b) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    return l;
}

ll check(ll b) {
    ll res = 0;
    for (int i = 1; i <= n; ++i) {
        res += Node{a[i] - a[i - 1], get(a[i] - a[i - 1], b)}.value();
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    std::cin >> m;

    for (int i = 1; i <= n; ++i) {
        node[i] = Node{a[i] - a[i - 1], 0};
    }

    ll t;
    {
        ll b = 0; // take all that benefit >= b
        for (int i = 60; ~i; --i) {
            if (check(b + (1ULL << i)) < m) {
                b += 1ULL << i;
            }
        }
        t = b + 1;
    }

    std::priority_queue<Node> q;
    ll tot = check(t);
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        q.push(Node{a[i] - a[i - 1], get(a[i] - a[i - 1], t)});
        ans += get(a[i] - a[i - 1], t);
    }

    while (tot > m) {
        auto [len, x] = q.top();
        q.pop();

        ll b = Node{len, x}.benefit();
        int l = x + 1, r = len;
        while (l < r) {
            int mid = (l + r + 1) / 2;
            if (Node{len, mid - 1}.benefit() == b &&
                tot - b * (mid - x - 1) > m) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        ans += l - x;
        tot -= b * (l - x);

        q.push(Node{len, l});
    }

    std::cout << ans << '\n';

    return 0;
}