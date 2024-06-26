#include <bits/stdc++.h>

constexpr int MAXS = 4e7;
constexpr int MAX_OP = 10;

inline constexpr bool is_boolean(const auto &x) {
    return x == 0 || x == 1;
}

struct Segment {
    struct Node {
        int ls, rs;
        int8_t val;
        bool tag;
    } tr[MAXS];
    int tot{MAX_OP};
    void ensure(int &x) {
        if (!x) {
            x = ++tot;
            tr[x].val = -1;
        }
    }
    void push_down(int node) {
        if (tr[node].tag) {
            const int ls = tr[node].ls;
            if (is_boolean(tr[ls].val)) {
                tr[ls].val ^= 1;
            }
            tr[ls].tag ^= 1;

            const int rs = tr[node].rs;
            if (is_boolean(tr[rs].val)) {
                tr[rs].val ^= 1;
            }
            tr[rs].tag ^= 1;

            tr[node].tag = false;
        }
    }
    int merge(int x, int y, int op) {
        if (is_boolean(tr[y].val)) {
            std::swap(x, y);
        }

        if (is_boolean(tr[x].val)) {
            if (is_boolean(tr[y].val)) {
                if (op == 4) {
                    tr[x].val &= tr[y].val;
                } else if (op == 6) {
                    tr[x].val |= tr[y].val;
                } else if (op == 5) {
                    tr[x].val ^= tr[y].val;
                } else {
                    assert(false);
                }
            } else {
                if (op == 4) {
                    if (tr[x].val == 0) {
                        tr[y].val = 0;
                    }
                } else if (op == 6) {
                    if (tr[x].val == 1) {
                        tr[y].val = 1;
                    }
                } else if (op == 5) {
                    if (tr[x].val == 1) {
                        tr[y].tag ^= 1;
                    }
                } else {
                    assert(false);
                }
                x = y;
            }
        } else {
            push_down(x);
            push_down(y);
            tr[x].ls = merge(tr[x].ls, tr[y].ls, op);
            tr[x].rs = merge(tr[x].rs, tr[y].rs, op);
        }
        return x;
    }
    int construct(int x, int l, int r) {
        int rt = 0;
        ensure(rt);

        auto set = [&](auto self, int node, int L, int R) -> void {
            if (R < x) {
                tr[node].val = 0;
                return;
            } else if (L >= x) {
                tr[node].val = 1;
                return;
            }
            int mid = (L + R) / 2;
            ensure(tr[node].ls);
            ensure(tr[node].rs);
            self(self, tr[node].ls, L, mid);
            self(self, tr[node].rs, mid + 1, R);
        };
        set(set, rt, l, r);
        return rt;
    }
    void reverse(int x) {
        if (is_boolean(tr[x].val)) {
            tr[x].val ^= 1;
        }
        tr[x].tag ^= 1;
    }
    bool query(int node, int L, int R, int x) {
        if (is_boolean(tr[node].val)) {
            return tr[node].val;
        }
        int mid = (L + R) / 2;
        push_down(node);
        if (x <= mid) {
            return query(tr[node].ls, L, mid, x);
        } else {
            return query(tr[node].rs, mid + 1, R, x);
        }
    }
} mt;

struct StringStream {
    std::string data;
    int front;
    StringStream(std::string s) : data(std::move(s)), front(0) {}
    int get() {
        if (front == data.size()) {
            return EOF;
        }
        return data[front++];
    }
    int peek() const {
        return data[front];
    }
    bool empty() {
        return front >= data.size();
    }
    int readInt() {
        char ch = get();
        while (!isdigit(ch)) {
            ch = get();
        }
        int res = 0;
        while (isdigit(ch)) {
            res = res * 10 + int(ch - 48);
            ch = get();
        }
        --front;
        return res;
    }
    int readOp() {
        char ch = get();
        while (ch != '!' && ch != '&' && ch != '^' && ch != '|') {
            ch = get();
        }
        if (ch == '!') {
            return 3;
        }
        if (ch == '&') {
            return 4;
        }
        if (ch == '^') {
            return 5;
        }
        return 6;
    }
};

constexpr int L = 1, R = 1e9;

int read_expr(StringStream &);
int read_atom(StringStream &ss) {
    char c = ss.peek();
    if (c == '(') {
        ss.get();
        int res = read_expr(ss);
        assert(ss.get() == ')');
        return res;
    }
    if (c == '[') {
        ss.get();
        int res = mt.construct(ss.readInt(), L, R);
        assert(ss.get() == ']');
        return res;
    }
    return ss.readOp();
}
int read_expr(StringStream &ss) {
    std::vector<int> st;
    while (!ss.empty() && ss.peek() != ')') {
        int x = read_atom(ss);
        if (x <= MAX_OP) {
            while (x != 3 && st.size() >= 3 && st[st.size() - 2] <= x) {
                int a = st[st.size() - 3], op = st[st.size() - 2],
                    b = st[st.size() - 1];
                st.resize(st.size() - 3);
                st.push_back(mt.merge(a, b, op));
            }
            st.push_back(x);
        } else {
            while (!st.empty() && st.back() == 3) {
                mt.reverse(x);
                st.pop_back();
            }
            st.push_back(x);
        }
    }
    while (st.size() >= 3) {
        int a = st[st.size() - 3], op = st[st.size() - 2],
            b = st[st.size() - 1];
        st.resize(st.size() - 3);
        st.push_back(mt.merge(a, b, op));
    }
    assert(st.size() == 1);
    return st.back();
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int n, q;
    std::cin >> n >> q;

    std::string s;
    std::cin >> s;
    StringStream ss{s};

    int rt = read_expr(ss);

    while (q--) {
        int x;
        std::cin >> x;
        if (mt.query(rt, L, R, x)) {
            std::cout << "True\n";
        } else {
            std::cout << "False\n";
        }
    }

    return 0;
}
