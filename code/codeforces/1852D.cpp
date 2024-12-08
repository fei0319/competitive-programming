#include <bits/stdc++.h>

using ll = long long int;

const int INF = 1e9;
const int MAXN = 1e6 + 19;

int n, k, suf[MAXN];
std::string s;

int max[MAXN][2], min[MAXN][2];
int from_max[MAXN][2], from_min[MAXN][2];

auto s_time = std::chrono::high_resolution_clock::now();

int code(char c) { return c == 'B'; }

void output(int i, int j, int from[][2]) {
    if (i == 0) {
        return;
    }
    output(i - 1, from[i][j], from);
    std::cout << (j ? 'B' : 'A');
}

std::mt19937 rng(time(nullptr));
std::string random_string() {
    static std::string t;
    t.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (rng() & 1) {
            t[i] = 'A';
        } else {
            t[i] = 'B';
        }
    }
    return t;
}

bool find(std::string t) {
    suf[n + 1] = 0;
    for (int i = n; i >= 1; --i) {
        suf[i] = suf[i + 1];
        if (i < n && t[i] != t[i + 1]) {
            suf[i] += 1;
        }
        if (t[i] != s[i]) {
            suf[i] += 1;
        }
    }

    if (k == suf[1]) {
        std::cout << "YES\n";
        std::cout << t.substr(1) << '\n';
        return true;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 2; ++j) {
            max[i][j] = -INF;
            min[i][j] = INF;
            if (i > 1) {
                for (int k = 0; k < 2; ++k) {
                    if (max[i - 1][k] + (j != k) > max[i][j]) {
                        max[i][j] = max[i - 1][k] + (j != k);
                        from_max[i][j] = k;
                    }
                    if (min[i - 1][k] + (j != k) < min[i][j]) {
                        min[i][j] = min[i - 1][k] + (j != k);
                        from_min[i][j] = k;
                    }
                }
            } else {
                max[i][j] = 0;
                min[i][j] = 0;
            }
            max[i][j] += (j != code(s[i]));
            min[i][j] += (j != code(s[i]));
            if (max[i][j] +
                    ((i < n) ? (j != code(t[i + 1])) + suf[i + 1] : 0) ==
                k) {
                std::cout << "YES\n";
                output(i, j, from_max);
                for (int p = i + 1; p <= n; ++p) {
                    std::cout << t[p];
                }
                std::cout << '\n';
                return true;
            }
            if (min[i][j] +
                    ((i < n) ? (j != code(t[i + 1])) + suf[i + 1] : 0) ==
                k) {
                std::cout << "YES\n";
                output(i, j, from_min);
                for (int p = i + 1; p <= n; ++p) {
                    std::cout << t[p];
                }
                std::cout << '\n';
                return true;
            }
        }
    }
    return false;
}

void solve() {
    std::cin >> n >> k;
    std::cin >> s;
    s = ' ' + s;

    for (int i = n - 1; i >= 1; --i) {
        if (s[i] != s[i + 1]) {
            k -= 1;
        }
    }
    if (k < 0) {
        std::cout << "NO\n";
        return;
    }

    if (find(s)) {
        return;
    }
    if (find(std::string(n + 1, 'A'))) {
        return;
    }
    if (find(std::string(n + 1, 'B'))) {
        return;
    }
    std::string t = s;
    for (int i = 1; i <= n; ++i) {
        t[i] = (t[i] == 'A' ? 'B' : 'A');
    }
    if (find(t)) {
        return;
    }

    for (int i = 0; i < 200; ++i) {
        //        for (int j = 0; j < 50; ++j) {
        if (find(random_string())) {
            return;
        }
        //        }
        //        if
        //        (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()
        //        - s_time).count() > 1600) {
        //            break;
        //        }
    }

    std::cout << "NO\n";
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