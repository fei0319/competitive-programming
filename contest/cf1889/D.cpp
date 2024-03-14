#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 1e6 + 19;

int n;
std::vector<int> r[MAXN];

int ans[MAXN];
int st[MAXN], top;
bool instack[MAXN];

void solve(int x) {
    st[top = 1] = x;
    instack[x] = true;
    
    while (top) {
        int u = st[top];
        if (ans[u] || r[u].empty()) {
            break;
        }
        int v = r[u].back();
        if (instack[v]) {
            while (st[top] != v) {
                r[st[top]].pop_back();
                instack[st[top]] = false;
                --top;
            }
            r[st[top]].pop_back();
        } else {
            st[++top] = v;
            instack[v] = true;
        }
    }

    int p = st[top];
    if (ans[p]) {
        p = ans[p];
    }

    while (top) {
        ans[st[top]] = p;
        instack[st[top]] = false;
        --top;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        int k;
        std::cin >> k;
        while (k--) {
            int t;
            std::cin >> t;
            r[i].push_back(t);
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (!ans[i]) {
            solve(i);
        }
    }

    for (int i = 1; i <= n; ++i) {
        std::cout << ans[i] << ' ';
    }

    return 0;
}