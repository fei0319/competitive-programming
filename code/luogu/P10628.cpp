#include <bits/stdc++.h>

void answer(std::vector<int>);

int query(std::vector<int>);
// QC = B
// C = Q^{-1}B
// B^{-1}Q = C^{-1}

void solve(int n) {
    std::vector<int> base(n);
    std::iota(base.begin(), base.end(), 0);

    int tot = query(base);
    for (int i = 0; i < n; ++i) {
        int pos = i;

        auto q{base};
        for (int j = 0; j < pos; ++j) {
            std::swap(q[j], q[j + 1]);
        }
        const int cnt = (tot + pos - query(q)) / 2;

        for (int _ = 0; _ < cnt; ++_) {
            int l = 0, r = pos;
            while (l < r) {
                int mid = (l + r) / 2;
                auto q{base};
                for (int j = mid; j < pos; ++j) {
                    std::swap(q[j], q[j + 1]);
                }

                if (query(q) >= tot + (pos - mid)) {
                    r = mid;
                } else {
                    l = mid + 1;
                }
            }
            if (l > 0) {
                --tot;
                std::swap(base[l - 1], base[pos]);
                pos = l - 1;
            } else {
                assert(false);
            }
        }
    }

    answer(base);
}