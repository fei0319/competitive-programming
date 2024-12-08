#include <bits/stdc++.h>
typedef long long int ll;
template <typename Tp>
void chkmax(Tp &a, const Tp &b) {
    a = std::max(a, b);
}
template <typename Tp>
void chkmin(Tp &a, const Tp &b) {
    a = std::min(a, b);
}
template <typename Tp>
void read(Tp &res) {
    static char ch;
    ch = getchar(), res = 0;
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) res = res * 10 + ch - 48, ch = getchar();
}

int main() {
    std::vector<int> p;
    for (int i = 1; i <= 5; ++i) {
        int t;
        read(t);
        p.push_back(t);
    }
    std::sort(p.begin(), p.end());
    printf("%d\n", (int)(std::unique(p.begin(), p.end()) - p.begin()));
}