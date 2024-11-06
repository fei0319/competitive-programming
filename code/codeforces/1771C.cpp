#include <bits/stdc++.h>

constexpr int maxn = 1e5 + 19;

int isprime[maxn], a[maxn];
std::vector<int> prime;
int cnt[maxn];

int n;
std::set<int> s;

void solve(void) {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];

    s.clear();
    for (int i : prime) cnt[i] = 0;

    for (int i = 1; i <= n; ++i) {
        int x = a[i];
        for (int p : prime) {
            if (x == 1) break;
            if (x % p == 0) {
                ++cnt[p];
                while (x % p == 0) x /= p;
            }
        }
        if (x != 1) {
            if (s.find(x) != s.end()) {
                std::cout << "YES\n";
                return;
            }
            s.insert(x);
        }
    }

    for (int i : prime)
        if (cnt[i] > 1) {
            std::cout << "YES\n";
            return;
        }

    std::cout << "NO\n";
}

int main() {
    constexpr int N = 4e4;
    for (int i = 2; i <= N; ++i) isprime[i] = 1;
    for (int i = 2; i <= N; ++i) {
        if (isprime[i]) {
            prime.push_back(i);
            int x = i + i;
            while (x <= N) {
                isprime[x] = 0;
                x += i;
            }
        }
    }

    int T;
    std::cin >> T;
    while (T--) solve();
}