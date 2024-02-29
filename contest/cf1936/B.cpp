#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 1e6 + 19;

int n;
std::string s;

struct BIT {
    ll tr[MAXN];
    ll query(int x) {
        x += 1;

        ll res = 0;
        for (; x; x -= x & -x) {
            res += tr[x];
        }
        return res;
    }
    ll query(int l, int r) {
        return query(r) - query(l - 1);
    }
    void update(int x, int k) {
        x += 1;
        
        for (; x <= n + 10; x += x & -x) {
            tr[x] += k;
        }
    }
} ml, mr;

int qL[MAXN], Ll, Lr;
int qR[MAXN], Rl, Rr;

void solve() {

    std::cin >> n;
    std::cin >> s;
    s = '>' + s + '<';

    Ll = 1, Lr = 0;
    Rl = 1, Rr = 0;
    for (int i = 0; i <= n + 1; ++i) {
        if (s[i] == '<') {
            qR[++Rr] = i;
        }

        if (s[i] == '>') {
            ml.update(i, i);
        } else {
            mr.update(i, i);
        }
    }

    qL[++Lr] = 0;
    for (int i = 1; i <= n; ++i) {
        if (s[i] == '<') {
            ++Rl;
        }

        int szL = Lr - Ll + 1, szR = Rr - Rl + 1;
        ll ans = 0;
        if (s[i] == '<') {
            if (szL <= szR) {
                ll L = ml.query(qL[Ll], qL[Lr]);
                ll R = 0;
                if (szL >= 2) {
                    R = mr.query(qR[Rl], qR[Rl + szL - 2]);
                }
                ans = R * 2 + i - L * 2;
            } else {
                ll L = 0;
                ll R = mr.query(qR[Rl], qR[Rr]);
                if (szR >= 1) {
                    L = ml.query(qL[Lr - szR + 1], qL[Lr]);
                }
                ans = R * 2 + i - L * 2 - (n + 1);
            }
        } else {
            if (szR <= szL) {
                ll L = 0;
                ll R = mr.query(qR[Rl], qR[Rr]);
                if (szR >= 2) {
                    L = ml.query(qL[Lr - szR + 2], qL[Lr]);
                }
                ans = R * 2 - i - L * 2 - (n + 1);
            } else {
                ll L = ml.query(qL[Ll], qL[Lr]);
                ll R = 0;
                if (szL >= 1) {
                    R = mr.query(qR[Rl], qR[Rl + szL - 1]);
                }
                ans = R * 2 - i - L * 2;
            }
        }

        std::cout << ans << ' ';

        if (s[i] == '>') {
            qL[++Lr] = i;
        }
    }
    std::cout << '\n';

    for (int i = 1; i <= n + 10; ++i) {
        ml.tr[i] = 0;
        mr.tr[i] = 0;
    }
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