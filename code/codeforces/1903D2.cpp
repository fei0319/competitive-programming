#include <bits/stdc++.h>

using ll = long long int;

const int B = 20;

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    for (int &i : a) {
        std::cin >> i;
    }

    std::vector<ll> b(1 << B);
    for (int i : a) {
        int S = 0;
        for (int j = B - 1; j >= 0; --j) {
            if (i & (1 << j)) {
                b[S | (1 << j)] += 1 << j;
            } else {
                S |= 1 << j;
            }
        }
    }

    std::vector<ll> c(1 << B);
    for (int S = 1; S < (1 << B); ++S) {
        ll res = 0;
        for (int s = S; s; s = S & (s - 1)) {
            res += b[s];
        }
        c[S] = res;
    }
    ll tot = std::accumulate(b.begin(), b.end(), 0ll);

    std::vector<std::pair<ll, ll>> save_and_cost;
    for (int S = 0; S < (1 << B); ++S) {
        ll x = tot - c[((1 << B) - 1) ^ S];
        ll v = (ll)n * S - x;
        save_and_cost.emplace_back(x, v);
    }
    std::sort(save_and_cost.begin(), save_and_cost.end());

    std::vector<std::pair<ll, ll>> st;
    for (auto [s, c] : save_and_cost) {
        while (!st.empty() && st.back().second >= c) st.pop_back();
        st.emplace_back(s, c);
    }

    while (q--) {
        ll k;
        std::cin >> k;

        int l = 0, r = st.size() - 1;
        while (l < r) {
            int mid = (l + r + 1) / 2;
            if (st[mid].second <= k) l = mid;
            else r = mid - 1;
        }

        std::cout << (k + st[l].first) / n << '\n';
    }

    return 0;
}