#include <bits/stdc++.h>

using ll = long long int;

int a, b, d;

ll mds(int a, int d) {
    ll k = 0ll;
    for (int i = 1; i <= a; i <<= 1)
        if ((a & i) && !(k & i))
            k += ((ll)d * i);
    return k;
}

void solve(void) {
    std::cin >> a >> b >> d;
    a |= b, b = a;

    if ((d & -d) > (a & -a)) {
        std::cout << -1 << std::endl;
        return;
    }
    int p = 0;
    while (!(d & 1))
        d >>= 1, a >>= 1, ++p;
    std::cout << (mds(a, d) << p) << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}