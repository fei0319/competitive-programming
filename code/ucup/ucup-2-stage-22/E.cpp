#include <bits/stdc++.h>

struct Chunk {
    int tot;
    std::vector<int> a;

    Chunk next(int n) {
        std::vector<int> res;
        for (int i = 0; i < n / tot; ++i) {
            res.insert(res.end(), a.begin(), a.end());
        }
        int rest = n % tot;
        for (int i = 0; rest && i < a.size(); ++i) {
            int v = std::min(rest, a[i]);
            res.push_back(v);
            rest -= v;
        }
        return Chunk{n, res};
    }
};

using vec_t = std::array<int, 26>;
vec_t operator-(const vec_t &lhs, const vec_t &rhs) {
    vec_t res{};
    for (int i = 0; i < res.size(); ++i) {
        res[i] = lhs[i] - rhs[i];
    }
    return res;
}
vec_t occ(const std::string &s) {
    vec_t res{};
    for (auto c : s) {
        res[c - 'a'] += 1;
    }
    return res;
}

std::string next_string(const std::string &s, int n) {
    std::string res(n, ' ');
    for (int i = 0; i < n; ++i) {
        res[i] = s[i % s.size()];
    }
    return res;
}

void solve() {
    int n;
    std::cin >> n;

    std::vector<std::string> s(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> s[i];
    }
    const int len = s[0].size();

    std::vector<Chunk> a(n);
    a[0] = Chunk{len, std::vector<int>{len}};

    std::vector<vec_t> sum(len + 1);
    std::vector<uint8_t> vist(len + 1);
    sum[len] = occ(s[0]);
    vist[len] = true;

    for (int i = 1; i < n; ++i) {
        a[i] = a[i - 1].next(s[i].size());
        if (!vist[a[i].a.back()]) {
            vec_t v = occ(s[i]);
            for (int x : a[i].a) {
                v = v - sum[x];
            }
            sum[a[i].a.back()] = v;
            vist[a[i].a.back()] = true;
        }
    }

    int last = 0;
    std::string start;
    for (int i = 1; i <= len; ++i) {
        if (!vist[i]) {
            continue;
        }
        if (std::accumulate(sum[i].begin(), sum[i].end(), 0) != i) {
            std::cout << "NO\n";
            return;
        }
        vec_t arr = sum[i] - sum[last];
        for (int j = 0; j < arr.size(); ++j) {
            if (arr[j] < 0) {
                std::cout << "NO\n";
                return;
            }
            if (arr[j]) {
                start.append(arr[j], char('a' + j));
            }
        }
        last = i;
    }

    std::vector<std::string> ans(n);
    ans[0] = start;
    for (int i = 1; i < n; ++i) {
        ans[i] = next_string(ans[i - 1], s[i].size());
    }
    for (int i = 0; i < n; ++i) {
        if (occ(ans[i]) != occ(s[i])) {
            std::cout << "NO\n";
            return;
        }
    }

    std::cout << "YES\n";
    for (int i = 0; i < n; ++i) {
        std::cout << ans[i] << '\n';
    }
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
