#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e5 + 19;

int n, m;
std::vector<int> G[maxn];

int fa[maxn];
int getf(int node) {
  return fa[node] == node ? node : fa[node] = getf(fa[node]);
}

void merge(int u, int v) {
  u = getf(u), v = getf(v);
  if (u != v) {
    fa[u] = v;
  }
}

bool is_neighbor[maxn], vist[maxn];
std::vector<int> E[maxn];

std::vector<std::pair<int, int>> ans;
bool dfs(int node, int targ) {
  vist[node] = true;
  if (node == targ) {
    return true;
  }
  for (int to : G[node]) {
    if (vist[to]) {
      continue;
    }
    if (dfs(to, targ)) {
      ans.emplace_back(node, to);
      return true;
    }
  }
  return false;
}

void output(int u, int x, int y) {
  std::cout << "YES\n";
  ans.clear();
  ans.emplace_back(u, x);
  ans.emplace_back(u, y);

  for (int i = 1; i <= n; ++i) {
    vist[i] = is_neighbor[i];
  }
  vist[x] = vist[y] = false;
  dfs(y, x);

  int flag = 0;
  for (int to : G[u]) {
    if (flag == 2) {
      break;
    }
    if (to != x && to != y) {
      ans.emplace_back(u, to);
      ++flag;
    }
  }

  std::cout << ans.size() << '\n';
  for (auto [u, v] : ans) {
    std::cout << u << ' ' << v << '\n';
  }
}

void dis(std::vector<int> &a) {
  std::sort(a.begin(), a.end());
  a.resize(std::unique(a.begin(), a.end()) - a.begin());
}

bool check(int u) {
  if ((int)G[u].size() < 4) {
    return false;
  }

  for (int i = 1; i <= n; ++i) {
    E[i].clear();
    fa[i] = i;
    is_neighbor[i] = false;
  }

  is_neighbor[u] = true;
  for (int to : G[u]) {
    is_neighbor[to] = true;
  }

  for (int i = 1; i <= n; ++i) {
    if (!is_neighbor[i]) {
      for (int to : G[i]) {
        if (!is_neighbor[to]) {
          merge(i, to);
        }
      }
    }
  }

  for (int i = 1; i <= n; ++i) {
    if (!is_neighbor[i]) {
      for (int to : G[i]) {
        if (is_neighbor[to])
          E[getf(i)].push_back(to);
      }
    }
  }

  for (int i = 1; i <= n; ++i) {
    dis(E[i]);
  }

  for (int i = 1; i <= n; ++i) {
    if (!is_neighbor[i] && getf(i) == i && (int)E[i].size() >= 2) {
      output(u, E[i][0], E[i][1]);
      return true;
    }
  }

  for (int i = 1; i <= n; ++i) {
    if (is_neighbor[i] && i != u) {
      for (int to : G[i]) {
        if (is_neighbor[to] && to != u) {
          output(u, i, to);
          return true;
        }
      }
    }
  }

  return false;
}

void solve(void) {
  std::cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    G[i].clear();
  }
  for (int i = 1, u, v; i <= m; ++i) {
    std::cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }

  for (int i = 1; i <= n; ++i) {
    if (check(i)) {
      return;
    }
  }
  std::cout << "NO\n";
  return;
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