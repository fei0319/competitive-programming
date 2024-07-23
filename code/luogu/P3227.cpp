#include <bits/stdc++.h>

template <class T>
struct Flow {
    static constexpr int INF = 1e9;
    int n;
    struct Edge {
        int to;
        T cap;
        Edge(int to, T cap) : to(to), cap(cap) {}
    };
    std::vector<Edge> edge;
    std::vector<std::vector<int>> adj;
    std::vector<int> cur, dep;
    Flow(int n) : n(n), adj(n) {}
    bool bfs(int s, int t) {
        dep.assign(n, -1);
        std::queue<int> q;
        dep[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            for (int i : adj[node]) {
                int to = edge[i].to;
                T c = edge[i].cap;
                if (c > 0 && dep[to] == -1) {
                    dep[to] = dep[node] + 1;
                    if (to == t) {
                        return true;
                    }
                    q.push(to);
                }
            }
        }
        return false;
    }
    T dfs(int node, int t, T flow) {
        if (node == t || flow == 0) {
            return flow;
        }
        T f, res = 0;
        for (int &i = cur[node]; i < int(adj[node].size()); ++i) {
            int j = adj[node][i];
            int to = edge[j].to;
            T c = edge[j].cap;

            if (dep[to] == dep[node] + 1 &&
                (f = dfs(to, t, std::min(flow, c)))) {
                res += f;
                flow -= f;
                edge[j].cap -= f;
                edge[j ^ 1].cap += f;
            }

            if (flow == 0) {
                break;
            }
        }
        if (!res) {
            dep[node] = -1;
        }
        return res;
    }
    int add_edge(int u, int v, T c) {
        int j = edge.size();
        adj[u].push_back(edge.size());
        edge.emplace_back(v, c);
        adj[v].push_back(edge.size());
        edge.emplace_back(u, 0);
        return j;
    }
    T operator()(int s, int t) {
        T ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, INF);
        }
        return ans;
    }
};

constexpr int INF = 1e9;
constexpr int N = 40;
constexpr int DX[]{1, -1, 0, 0}, DY[]{0, 0, 1, -1};
int v[N][N][N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int a, b, c;
    std::cin >> a >> b >> c;

    int d;
    std::cin >> d;

    for (int z = 0; z < c; ++z) {
        for (int x = 0; x < a; ++x) {
            for (int y = 0; y < b; ++y) {
                std::cin >> v[x][y][z];
            }
        }
    }

    auto coord = [&](int x, int y, int z) {
        return x * b * (c + 1) + y * (c + 1) + z;
    };

    auto f = Flow<int>{a * b * (c + 1) + 2};
    const int s = a * b * (c + 1), t = a * b * (c + 1) + 1;
    for (int x = 0; x < a; ++x) {
        for (int y = 0; y < b; ++y) {
            f.add_edge(s, coord(x, y, 0), INF);
            for (int z = 0; z < c; ++z) {
                f.add_edge(coord(x, y, z), coord(x, y, z + 1), v[x][y][z]);
            }
            f.add_edge(coord(x, y, c), t, INF);
            for (int _ = 0; _ < 4; ++_) {
                int nx = x + DX[_], ny = y + DY[_];
                if (nx >= 0 && nx < a && ny >= 0 && ny < b) {
                    for (int z = d; z < c; ++z) {
                        f.add_edge(coord(x, y, z), coord(nx, ny, z - d), INF);
                    }
                }
            }
        }
    }

    std::cout << f(s, t) << '\n';
}
