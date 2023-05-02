#include <bits/stdc++.h>

using i64 = long long int;

constexpr int MOD = 998244353;

template <typename Tp> Tp qpow(Tp a, int b) {
    Tp res = 1;
    while (b) {
        if (b & 1)
            res *= a;
        a *= a, b >>= 1;
    }
    return res;
}

int norm(int x) {
    if (x < 0) {
        x += MOD;
    }
    if (x >= MOD) {
        x -= MOD;
    }
    return x;
}

struct Z {
    int x;
    Z(int x = 0) : x(norm(x)) {}
    Z(i64 x) : x(norm(x % MOD)) {}
    int val() const { return x; }
    Z operator-() const { return Z(norm(MOD - x)); }
    Z inv() const {
        assert(x != 0);
        return qpow(*this, MOD - 2);
    }
    Z &operator*=(const Z &rhs) {
        x = i64(x) * rhs.x % MOD;
        return *this;
    }
    Z &operator+=(const Z &rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    Z &operator-=(const Z &rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    Z &operator/=(const Z &rhs) { return *this *= rhs.inv(); }
    friend Z operator*(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res *= rhs;
        return res;
    }
    friend Z operator+(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res += rhs;
        return res;
    }
    friend Z operator-(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res -= rhs;
        return res;
    }
    friend Z operator/(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res /= rhs;
        return res;
    }
    friend std::istream &operator>>(std::istream &is, Z &a) {
        i64 v;
        is >> v;
        a = Z(v);
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const Z &a) {
        return os << a.val();
    }
};

int n, id[256];
char c[] = {'w', 'i', 'n'};
std::vector<int> t[3][3];
// lack _ and abu _

bool ok() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (!t[i][j].empty())
                return false;
    return true;
}

void solve(void) {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::string s;
        std::cin >> s;
        std::vector<int> a, b;
        int cnt[3] = {0, 0, 0};
        for (int j = 0; j < 3; ++j)
            ++cnt[id[(int)s[j]]];
        for (int j = 0; j < 3; ++j) {
            while (cnt[j] < 1)
                ++cnt[j], a.push_back(j);
            while (cnt[j] > 1)
                --cnt[j], b.push_back(j);
        }
        for (int j = 0; j < a.size(); ++j)
            t[a[j]][b[j]].push_back(i);
    }
    std::vector<std::string> ans;
    static char tmp[200];
    while (!ok()) {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                while (!t[i][j].empty() && !t[j][i].empty()) {
                    std::sprintf(tmp, "%d %c %d %c\n", t[i][j].back(), c[j],
                                 t[j][i].back(), c[i]);

                    t[i][j].pop_back();
                    t[j][i].pop_back();

                    ans.push_back(tmp);
                }
            }
        bool flag = 0;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j)
                if (!t[i][j].empty()) {
                    for (int k = 0; k < 3; ++k)
                        if (!t[j][k].empty()) {
                            std::sprintf(tmp, "%d %c %d %c\n", t[i][j].back(),
                                         c[j], t[j][k].back(), c[k]);

                            t[i][k].push_back(t[i][j].back());
                            t[i][j].pop_back();
                            t[j][k].pop_back();

                            ans.push_back(tmp);

                            flag = 1;
                            break;
                        }
                    if (flag)
                        break;
                }
            if (flag)
                break;
        }
    }

    std::cout << ans.size() << '\n';
    for (auto &s : ans)
        std::cout << s;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    id[(int)'w'] = 0;
    id[(int)'i'] = 1;
    id[(int)'n'] = 2;

    while (T--) {
        solve();
    }

    return 0;
}