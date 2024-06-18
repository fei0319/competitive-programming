#include <bits/stdc++.h>

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    int n;
    std::cin >> n;

    auto query = [](int x, int y) {
        std::cout << "? " << x << ' ' << y << std::endl;
        std::string s;
        std::cin >> s;
        return s == "YES";
    };

    std::vector<int> col(n + 1), st;
    int x = 0, y = 0;
    for (int i = 1; i <= n; ++i) {
        if (!st.empty()) {
            if (query(st.back(), i)) {
                st.push_back(i);
            } else if (!x || query(x, i)) {
                col[i] = 0;
                x = i;

                y = st.back();
                for (int j : st) {
                    col[j] = 1;
                }
                st.clear();
            } else {
                col[i] = 1;
                y = i;

                x = st.back();
                for (int j : st) {
                    col[j] = 0;
                }
                st.clear();
            }
        } else {
            bool qx = !x || query(x, i), qy = !y || query(y, i);
            assert(qx || qy);
            if (qx && qy) {
                st.push_back(i);
            } else if (qx) {
                col[i] = 0;
                x = i;
            } else if (qy) {
                col[i] = 1;
                y = i;
            }
        }
    }

    std::cout << "! ";
    for (int i = 1; i <= n; ++i) {
        std::cout << col[i] << ' ';
    }
    std::cout << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}