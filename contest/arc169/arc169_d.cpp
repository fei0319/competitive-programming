#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 3e5 + 19;

int n, m, cnt[MAXN];
int s[MAXN], sum[MAXN];

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b) {
        int res = exgcd(b, a % b, y, x);
        y -= (a / b) * x;
        return res;
    } else {
        x = 1, y = 0;
        return a;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        int a;
        std::cin >> a;
        cnt[a] += 1;
    }

    for (int i = 0; i < n; ++i) {
        s[i] = 1 - cnt[i];
        if (i >= 1) {
            s[i] += s[i - 1];
        }
    }
    
    ll x = 0;
    for (int i = 0; i < n; ++i) {
        if (cnt[i] > 1) {
            x = (x - (ll)i * (cnt[i] - 1));
        } else if (cnt[i] == 0) {
            x = (x + i);
        }
    }
    x += (ll)*std::max_element(s, s + n) * n;

    int max_d = 0, min_s = 0;
    int base = std::max_element(s, s + n) - s + 1;
    for (int i = 0, v = 0; i < n; ++i) {
        int now = (base + i) % n;
        v += 1 - cnt[now];
        max_d = std::max(max_d, v - min_s);
        min_s = std::min(min_s, v);
    }

    ll u, v, g;
    g = exgcd(n, m, u, v);

    if (x % g == 0) {
        int p = n / g;
        v = (ll)v * (x / g) % p;
        v = (v + p) % p;
        // v * m >= x
        // v >= ceil(x / m)
        auto lift = [p](ll v, ll to) {
            if (v < to) {
                ll d = to - v;
                v += (d + p - 1) / p * p;
            }
            return v;
        };

        v = lift(v, (x + m - 1) / m);

        ll next = lift(v, max_d + (v * m - x) / n);
        while (next > v) {
            v = next;
            next = lift(v, max_d + (v * m - x) / n);
        }

        std::cout << v << '\n';
    } else {
        std::cout << "-1\n";
    }

    return 0;
}