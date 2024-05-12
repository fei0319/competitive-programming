#include <bits/stdc++.h>

int n;

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        std::cin >> n;
        int cntn = 0, cntp = 0;
        while (n--) {
            int a;
            std::cin >> a;
            if (a == -1)
                ++cntn;
            else
                ++cntp;
        }
        // std::cout << cntn << ' ' << cntp << '\n';
        if (cntn <= cntp) {
            std::cout << cntn % 2 << '\n';
        } else {
            int tag = (cntn + cntp + 1) / 2;
            if ((cntn + cntp - tag) % 2)
                ++tag;
            std::cout << tag - cntp << '\n';
        }
    }
}