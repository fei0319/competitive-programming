#include <iostream>
#include <vector>

const int MAXN = 2e5 + 19;

int n, a[MAXN], b[MAXN];
int deg[MAXN];
std::vector<int> G[MAXN];

int exclude;
bool vist[MAXN], instack[MAXN];
int st[MAXN], top;
bool dfs(int node) {
    vist[node] = true;
    st[++top] = node;
    instack[node] = true;


    for (int to : G[node]) {
        if (to == exclude) {
            continue;
        }
        if (instack[to]) {
            return true;
        }
        if (!vist[to] && dfs(to)) {
            return true;
        }
    }
    --top;
    instack[node] = false;

    return false;
}

void solve() {
    std::cin >> n;
    std::fill(deg, deg + 1 + n, 0);
    for (int i = 0; i <= n; ++i) {
        G[i].clear();
    }

    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        std::cin >> b[i];
        G[b[i]].push_back(a[i]);
        ++deg[b[i]];
    }

    if (n == 1) {
        std::cout << "AC\n";
        return;
    }

    std::fill(vist, vist + n + 1, false);
    std::fill(instack, instack + n + 1, false);
    exclude = std::max_element(deg + 1, deg + 1 + n) - deg;
    for (int i = 1; i <= n; ++i) {
        if (i != exclude && dfs(i)) {
            std::cout << "WA\n";
            return;
        }
    }
    std::cout << "AC\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }
}