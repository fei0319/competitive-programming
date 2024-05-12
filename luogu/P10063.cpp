#include <bits/stdc++.h>

template <class T>
void read(T &res) {
    res = 0;
    char ch;
    std::cin.get(ch);
    while (!isdigit(ch)) {
        std::cin.get(ch);
    }
    while (isdigit(ch)) {
        res = res * 10 + (ch - 48);
        std::cin.get(ch);
        if (std::cin.eof()) {
            break;
        }
    }
}

using i128 = __int128;
using u64 = uint64_t;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<i128> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        read(a[i]);
    }

    auto is_prime = [](int x) -> bool {
        if (x == 1) {
            return false;
        }
        for (int i = 2; i * i <= x; ++i) {
            if (x % i == 0) {
                return false;
            }
        }
        return true;
    };

    std::vector<u64> b(n + 1);
    const int T = 100;
    for (int _ = 0; _ < T; ++_) {
        auto rnd = std::uniform_int_distribution<int>(1e6, 5e6);
        int P = 1;
        while (!is_prime(P)) {
            P = rnd(rng);
        }
        std::vector<uint8_t> is_square(P);
        for (int i = 1; i < P; ++i) {
            is_square[(u64)i * i % P] = true;
        }

        const u64 hash_val =
            std::uniform_int_distribution<u64>(1, 0ULL - 1ULL)(rng);
        for (int i = 1; i <= n; ++i) {
            i128 x = a[i];
            while (x % P == 0) {
                x /= P;
            }
            x %= P;
            if (!is_square[x]) {
                b[i] ^= hash_val;
            }
        }
    }

    std::unordered_map<u64, std::vector<int>> pos;
    pos[0].push_back(0);
    for (int i = 1; i <= n; ++i) {
        b[i] ^= b[i - 1];
        pos[b[i]].push_back(i);
    }

    u64 ans = 0;
    for (auto &[k, v] : pos) {
        ans += v.size() * (v.size() - 1) / 2;
        std::reverse(v.begin(), v.end());
    }

    std::cout << ans << '\n';
    int rest_to_output = 1e5;
    for (int l = 1; l <= n; ++l) {
        auto &v = pos[b[l - 1]];
        v.pop_back();
        for (auto it = v.rbegin(); it != v.rend(); ++it) {
            if (!rest_to_output) {
                break;
            }
            --rest_to_output;
            std::cout << l << ' ' << *it << '\n';
        }
        if (!rest_to_output) {
            break;
        }
    }

    return 0;
}