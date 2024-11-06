#include <cctype>
#include <cstdio>

template <typename Tp>
void read(Tp &res) {
    static char ch;
    ch = getchar(), res = 0;
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) res = res * 10 + ch - 48, ch = getchar();
}

constexpr int maxn = 1e3 + 19;

int n, m;
int p[maxn][maxn], q[maxn][maxn];

constexpr int mod = 998244353;
struct mod_t {
    int x;
    mod_t(int _x = 0) { x = _x; }
    mod_t operator+(const mod_t &b) const { return (x + b.x) % mod; }
    mod_t operator*(const mod_t &b) const {
        return (long long int)x * b.x % mod;
    }
};

mod_t count_white() {
    static mod_t prep[maxn][maxn], preq[maxn][maxn];
    static mod_t sufp[maxn][maxn], sufq[maxn][maxn];

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j)
            prep[i][j] = (mod_t)p[i][j] + prep[i][j - 1];
        for (int j = m; j >= 1; --j)
            sufp[i][j] = (mod_t)p[i][j] + sufp[i][j + 1];
    }
    for (int j = 1; j <= m; ++j) {
        for (int i = 1; i <= n; ++i)
            preq[i][j] = (mod_t)q[i][j] + preq[i - 1][j];
        for (int i = n; i >= 1; --i)
            sufq[i][j] = (mod_t)q[i][j] + sufq[i + 1][j];
    }

    mod_t res;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            res = res + prep[i][j - 1] * preq[i - 1][j] *
                            (i < n ? sufp[i + 1][j] : 0) *
                            (j < m ? sufq[i][j + 1] : 0);
        }
    return res + 1;
}

mod_t count_black() { return 1; }

int main() {
    read(n), read(m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) read(p[i][j]);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) read(q[i][j]);
    printf("%d\n", (count_white() + count_black()).x);
}