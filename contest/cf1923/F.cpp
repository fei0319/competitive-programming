#include <iostream>
#include <vector>
#include <algorithm>

using ull = unsigned long long int;
const int MOD = 1e9 + 7;

const ull BASE = 998244353;

std::string no_reverse(std::string s, int k) {
    int pos = 0;

    for (int i = 0; i < k; ++i) {
        while (!s.empty() && s.back() == '0') {
            s.pop_back();
        }
        while (pos < s.size() && s[pos] != '0') ++pos;
        if (pos < s.size() - 1) {
            std::swap(s[pos], s.back());
        }
    }

    while (!s.empty() && s.back() == '0') {
        s.pop_back();
    }
    return s;
}

int value(std::string s) {
    int res = 0, base = 1;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '1') {
            res = (res + base) % MOD;
        }
        base = (base + base) % MOD;
    }
    return res;
}

bool comp(std::string x, std::string y) {
    while (!x.empty() && x.back() == '0') {
        x.pop_back();
    }
    while (!y.empty() && y.back() == '0') {
        y.pop_back();
    }

    if (x.size() != y.size()) {
        return x.size() < y.size();
    }
    for (int i = x.size(); i >= 0; --i) {
        if (x[i] != y[i]) {
            return x[i] < y[i];
        }
    }
    return false;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::string s;

    std::cin >> n >> k >> s;

    std::reverse(s.begin(), s.end());
    std::string __s = no_reverse(s, k);

    k -= 1;

    int cnt = std::count(s.begin(), s.end(), '1');
    if (cnt <= k) {
        s = std::string(cnt, '1');
    } else {
        std::vector<int> a;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '1') {
                a.push_back(i);
            }
        }

        std::vector<ull> h(s.size()), b(s.size());
        b[0] = 1;
        for (int i = 1; i < s.size(); ++i) {
            b[i] = b[i - 1] * BASE;
        }
        for (int i = 0; i < s.size(); ++i) {
            h[i] = (i ? h[i - 1] : 0ULL) * BASE + ull(s[i]);
        }
        auto get_hash = [&](int l, int r) -> ull {
            if (l == 0) {
                return h[r];
            }
            return h[r] - h[l - 1] * b[r - l + 1];
        };

        auto cmp = [&](std::pair<int, int> _x, std::pair<int, int> _y) -> bool {
            int x = _x.first, y = _y.first;
            int l = 0, r = _x.second - _x.first + 1;
            while (l < r) {
                int mid = (l + r + 1) / 2;
                if (get_hash(x, x + mid - 1) == get_hash(y, y + mid - 1)) {
                    l = mid;
                } else {
                    r = mid - 1;
                }
            }

            if (l == _x.second - _x.first + 1) {
                return false;
            }
            return s[x + l] < s[y + l];
        };

        // a[0] to a[i-1] must be relocated
        // a[a.size() - (k-i)] to a[a.size() - 1] must be relocated
        std::vector<std::pair<int, int>> mins;

        for (int i = 0; i <= k; ++i) {
            int l = i, r = a.size() - (k - i) - 1;
            if (a[r] - a[l] - (r - l) <= k) {
                std::cout << value(std::string(cnt, '1')) << '\n';
                return 0;
            }
            if (mins.empty() || a[r] - a[l] < mins[0].second - mins[0].first) {
                mins.clear();
                mins.emplace_back(a[l], a[r]);
            } else if (!mins.empty() && a[r] - a[l] == mins[0].second - mins[0].first) {
                mins.emplace_back(a[l], a[r]);
            }
        }

        auto [l, r] = *std::min_element(mins.begin(), mins.end(), cmp);
        s = s.substr(l, r - l + 1);
        std::reverse(s.begin(), s.end());
        for (int i = 0; i < s.size() && k > 0; ++i) {
            if (s[i] == '0') {
                s[i] = '1';
                k -= 1;
            }
        }
    }

    s = std::min(s, __s, comp);
    std::cout << value(s) << '\n';
}