#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <ctime>

int n, T;
std::string S;
int query(std::string s) {
    T += 1;
    int res = 0;
    std::cout << s << std::endl;
    std::cin >> res;
//        for (int i = 0; i < n; ++i) {
//            if (s[i] == S[i]) {
//                ++res;
//            }
//        }

    if (res == n) {
//        std::cout << T << '\n';
        exit(0);
    }
    if (res == -1) {
        exit(0);
    }
    return res;
}

std::vector<int> a;
std::vector<std::pair<int, int>> p;
std::string ans;

int tot;
void solve(int l, int r, int cnt) {
    if (cnt == 0 || cnt == r - l + 1) {
        char c = (cnt == 0) ? 'F' : 'T';
        for (int i = l; i <= r; ++i) {
            ans[a[i]] = c;
        }
        return;
    }
    if (r - l + 1 == 2) {
        p.emplace_back(a[l], a[r]);
        return;
    }
    static std::string s;
    s.resize(n);
    int mid = (l + r) / 2;
    for (int i = 0; i < n; ++i) {
        s[i] = 'T';
    }
    for (int i = mid + 1; i <= r; ++i) {
        s[a[i]] = 'F';
    }
    int t = query(s);
    // cnt = L + R
    // t = L + (r - mid - R) + tot - cnt
    // L = (cnt + t - (r - mid) - (tot - cnt)) / 2

    int L = (cnt + t - (r - mid) - (tot - cnt)) / 2, R = cnt - L;
    solve(l, mid, L);
    solve(mid + 1, r, R);
}

std::mt19937 rng(time(nullptr));
char rev(char c) {
    return c == 'T' ? 'F' : 'T';
}

int main() {
    std::cin >> n;

    S.resize(n);
    for (int i = 0; i < n; ++i) {
        S[i] = rng() % 2 ? 'T' : 'F';
    }

    ans.resize(n);
    a.resize(n);
    std::iota(a.begin(), a.end(), 0);
    std::shuffle(a.begin(), a.end(), rng);

    solve(0, n - 1, tot = query(std::string(n, 'T')));


    std::function<void(std::vector<std::pair<int, int>>)> set_up = [&](std::vector<std::pair<int, int>> p) {
        std::vector<std::pair<int, int>> a, b;
        while (p.size() >= 2) {
            auto [x1, y1] = p.back();
            p.pop_back();
            auto [x2, y2] = p.back();
            p.pop_back();

            static std::string s;
            s.resize(n);
            for (int i = 0; i < n; ++i) {
                s[i] = 'T';
            }
            s[x1] = s[x2] = 'F';

            int t = query(s);
            if (t == tot - 2) {
                ans[x1] = ans[x2] = 'T';
                ans[y1] = ans[y2] = 'F';
            } else if (t == tot + 2) {
                ans[x1] = ans[x2] = 'F';
                ans[y1] = ans[y2] = 'T';
            } else {
                a.emplace_back(x1, y1);
                b.emplace_back(x2, y2);
            }
        }
        if (!p.empty()) {
            auto [x, y] = p.back();
            std::string s(n, 'T');
            s[x] = 'F';

            if (query(s) == tot + 1) {
                ans[x] = 'F', ans[y] = 'T';
            } else {
                ans[x] = 'T', ans[y] = 'F';
            }
        }
        if (!a.empty()) {
            set_up(a);
        }
        for (int i = 0; i < a.size(); ++i) {
            ans[b[i].first] = rev(ans[a[i].first]);
            ans[b[i].second] = rev(ans[a[i].second]);
        }
    };

    set_up(p);
    query(ans);
}