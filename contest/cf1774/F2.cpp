#include <bits/stdc++.h>

using ll = long long int;

template <typename T>
constexpr int INF = 1e9;

template <>
constexpr ll INF<ll> = 1e18;

const int MAXN = 1e6 + 19;
const int MOD = 998244353;

int n;

std::vector<ll> a;
int op[MAXN];
ll s[MAXN];

int p[MAXN];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    p[0] = 1;
    for (int i = 1; i <= n; ++i) {
        p[i] = p[i - 1] * 2 % MOD;
        s[i] += s[i - 1];
        s[i] = std::min(s[i], INF<ll>);

        int t;
        std::cin >> t;
        if (t == 3) {
            op[i] = 0;
            s[i + 1] += s[i];
        } else {
            std::cin >> op[i];
            if (t == 2) {
                s[i] += op[i];
                op[i] = -op[i];
            }
        }
        s[i] = std::min(s[i], INF<ll>);
    }

    ll d = 1LL;
    auto solve = [&d](int x) -> int64_t {
        if (x < d) {
            return 0LL;
        }
        x -= d;
        int res = 1;
        for (int i = a.size(); i >= 1; --i) {
            if (a[a.size() - i] == 0) {
                res = (res + p[i] - 1) % MOD;
                break;
            }
            if (x >= a[a.size() - i]) {
                x -= a[a.size() - i];
                res = (res + p[i - 1]) % MOD;
            }
        }
        return res;
    };

    int ans = 0;
    for (int i = n; i >= 1; --i) {
        if (op[i] > 0) {
            ans = (ans + solve(op[i])) % MOD;
        } else if (op[i] < 0) {
            d -= op[i];
        } else if (s[i] <= INF<int>) {
            a.push_back(s[i]);
        }
    }
    std::cout << (ans + MOD) % MOD << '\n';

    return 0;
}