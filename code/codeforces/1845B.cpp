#include <algorithm>
#include <cmath>
#include <cstdio>

int x[2][3];

void solve() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 2; ++j) scanf("%d", &x[j][i]);

    int ans = 0;
    for (int i = 0; i < 2; ++i) {
        if (x[i][1] == x[i][0] || x[i][2] == x[i][0]) ans += 0;
        else if ((x[i][1] < x[i][0]) != (x[i][2] < x[i][0]))
            ans += 0;
        else
            ans +=
                std::min(abs(x[i][1] - x[i][0]), abs(x[i][2] - x[i][0]));
    }
    printf("%d\n", ans + 1);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
}