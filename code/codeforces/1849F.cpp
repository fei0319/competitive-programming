#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 2e5 + 19;
const int B = 29;

int n, a[MAXN];

std::vector<std::vector<int>> G;
std::vector<uint8_t> vist, col;

void dfs(int node) {
    vist[node] = true;
    for (int to : G[node]) {
        if (!vist[to]) {
            col[to] = !col[node];
            dfs(to);
        }
    }
}

bool check(int x, int mask) {
    auto _G = G;

    std::unordered_map<int, std::vector<int>> mt;
    for (int i = 0; i < n; ++i) {
        mt[a[i] & mask].push_back(i);
    }

    bool res = true;
    if (x == 0) {
        for (auto &[k, v] : mt) {
            if (v.size() > 2) {
                res = false;
                break;
            } else if (v.size() == 2) {
                G[v[0]].push_back(v[1]);
                G[v[1]].push_back(v[0]);
            }
        }
    } else {
        std::unordered_map<int, int> id;
        for (auto &[k, v] : mt) {
            if (!mt.contains(k ^ x)) continue;
            int p = G.size();
            id[k] = p;
            G.push_back(std::vector<int>());
            for (int i : v) {
                G[i].push_back(p);
                G[p].push_back(i);
            }
        }
        for (auto &[k, v] : mt) {
            if (mt.contains(k ^ x)) {
                int p = id[k], q = id[k ^ x];
                G[p].push_back(q);
                G[q].push_back(p);
            }
        }
    }

    if (res) {
        vist.resize(G.size());
        col.resize(G.size());
        std::fill(vist.begin(), vist.end(), false);
        for (int i = 0; i < G.size(); ++i) {
            if (!vist[i]) {
                dfs(i);
            }
        }
        for (int i = 0; i < G.size(); ++i) {
            for (int to : G[i]) {
                if (col[i] == col[to]) {
                    res = false;
                }
            }
        }
    }

    if (!res) {
        _G.swap(G);
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    G.resize(n);

    if (n == 2) {
        std::cout << "10" << '\n';
        return 0;
    }

    int ans = 0;
    for (int i = B; i >= 0; --i) {
        if (check(ans, (1 << 30) - (1 << i))) {
            ans |= 1 << i;
        }
    }

    std::fill(vist.begin(), vist.end(), false);
    for (int i = 0; i < G.size(); ++i) {
        if (!vist[i]) {
            dfs(i);
        }
    }
    for (int i = 0; i < n; ++i) {
        std::cout << int(col[i]);
    }
    std::cout << '\n';

    return 0;
}