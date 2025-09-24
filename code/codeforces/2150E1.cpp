#include <bits/stdc++.h>

bool ask(const std::vector<int> &S, int x) {
    std::cout << std::format("? {} {} ", x, S.size());
    for (int i : S) std::cout << i << ' ';
    std::cout << std::endl;

    int res;
    std::cin >> res;
    return res;
}

void answer(int y) { std::cout << "! " << y << std::endl; }

std::mt19937 rng(std::random_device{}());
int work(std::vector<int> a, std::vector<int> f, std::vector<int> g) {
    assert(f.size() * 2 + g.size() == a.size() + 1);
    if (f.size() == 1) return f[0];

    std::shuffle(a.begin(), a.end(), rng);

    std::vector<int> L(a.begin(), a.begin() + a.size() / 2), Lf, Lg;
    std::vector<int> R(a.begin() + a.size() / 2, a.end()), Rf, Rg;

    for (int x : g) {
        if (ask(L, x)) {
            Lg.push_back(x);
        } else {
            Rg.push_back(x);
        }
    }
    for (int x : f) {
        if (ask(L, x)) {
            if (ask(R, x)) {
                Lg.push_back(x);
                Rg.push_back(x);
            } else {
                Lf.push_back(x);
            }
        } else {
            Rf.push_back(x);
        }
    }

    if (Lf.size() * 2 + Lg.size() == L.size() + 1) {
        return work(L, Lf, Lg);
    } else if (Rf.size() * 2 + Rg.size() == R.size() + 1) {
        return work(R, Rf, Rg);
    }
    exit(-1);
}

auto solve() -> void {
    int n;
    std::cin >> n;

    std::vector<int> a(n * 2 - 1);
    std::iota(a.begin(), a.end(), 1);
    std::vector<int> f(n);
    std::iota(f.begin(), f.end(), 1);

    answer(work(a, f, {}));
}

int main() {
    int t;
    std::cin >> t;

    for (auto _ : std::views::iota(0, t)) solve();
}
