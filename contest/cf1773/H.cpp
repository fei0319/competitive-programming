#include <bits/stdc++.h>

using ll = long long int;

const int T = 1e6;

std::string query(int x, int y) {
    std::cout << x << ' ' << y << std::endl;
    std::string res;
    std::getline(std::cin, res);

    if (res.ends_with('!')) {
        exit(0);
    }
    return res;
}

void try_with_x(int x, int alterX, const std::string &equal) {
    query(x, 0);
    std::string u = query(x, 1);
    query(x, T);
    std::string v = query(x, T - 1);

    std::string closer = u;
    int l = 0, r = T;
    while (l < r) {
        query(x, l);
        std::string s = query(x, r);
        if (s == equal) {
            query(x, (l + r) / 2);
            query(alterX, (l + r) / 2);
        } else if (s == closer) {
            l = (l + r) / 2 + 1;
        } else {
            r = (l + r + 1) / 2 - 1;
        }
    }
    query(x, l);
    query(alterX, l);
}

int main() {
    query(0, 0);
    std::string equal = query(0, 0);

    std::string closer;
    {
        std::string u = query(1, 0);
        query(T, 0);
        std::string v = query(T - 1, 0);
        if (u != v) {
            try_with_x(0, T, equal);
            return 0;
        }
        closer = u;
    }

    int lx = 1, rx = T - 1, ly = 0, ry = T;
    while (lx < rx || ly < ry) {
        query(lx, ly);
        std::string u = query(rx, ly), v = query(rx, ry);

        if (u == equal) {
            lx = rx = (lx + rx) / 2;
        } else if (u == closer) {
            lx = (lx + rx) / 2 + 1;
        } else {
            rx = (lx + rx + 1) / 2 - 1;
        }

        if (v == equal) {
            ly = ry = (ly + ry) / 2;
        } else if (v == closer) {
            ly = (ly + ry) / 2 + 1;
        } else {
            ry = (ly + ry + 1) / 2 - 1;
        }
    }

    query(lx, ly);

    return 0;
}