#include <algorithm>
#include <cstdio>
#include <cstring>

using ll = long long int;
using ull = unsigned long long int;

constexpr int maxn = 1e5 + 19;
char s[maxn], t[maxn];
int n;

constexpr int mod = 998244357, seed = 17;
constexpr ull useed = 12392483891;
int base[maxn];
ull ubase[maxn];

struct Hasher {
    struct Hash_t {
        int val, len;
        ull tal;
        bool operator==(const Hash_t &b) const {
            return val == b.val && tal == b.tal && len == b.len;
        }
        Hash_t operator+(const Hash_t &b) const {
            Hash_t res;
            res.val = ((ll)val * base[b.len] + b.val) % mod;
            res.tal = tal * ull(ubase[b.len]) + b.tal;
            res.len = len + b.len;
            return res;
        }
        Hash_t operator-(const Hash_t &b) const {
            Hash_t res;
            res.val =
                ((val - (ll)b.val * base[len - b.len]) % mod + mod) % mod;
            res.tal = tal - b.tal * ull(ubase[len - b.len]);
            res.len = len - b.len;
            return res;
        }
    } a[maxn], b[maxn];
    void init(char *s) {
        for (int i = 1; i <= n; ++i) {
            Hash_t tmp;
            tmp.val = s[i] + 8, tmp.tal = s[i] + 7, tmp.len = 1;
            a[i] = b[i] = tmp;
            //    printf("%d\n", tmp.val);
        }
        for (int i = 1; i <= n; ++i) a[i] = a[i - 1] + a[i];
        for (int i = n; i >= 1; --i) b[i] = b[i + 1] + b[i];
    }
    Hash_t code(int l, int r) { return a[r] - a[l - 1]; }
    Hash_t rcode(int l, int r) { return b[l] - b[r + 1]; }
    Hash_t operator()(int L, int R, int l, int r) {
        if (l > R) return code(L, R);
        if (r <= R) return code(L, l - 1) + rcode(l, r) + code(r + 1, R);
        int len = R - l + 1;
        return code(L, l - 1) + rcode(r - len + 1, r);
    }
} hashS, hashT;

bool brute_judge(int l, int r) {
    //    printf("%d %d\n", l, r);
    for (int i = 1; l + i - 1 < r - i + 1; ++i)
        std::swap(s[l + i - 1], s[r - i + 1]);
    //    puts(s + 1);
    bool ans = true;
    for (int i = 1; i < n - i + 1; ++i)
        if (s[i] != s[n - i + 1]) ans = false;
    for (int i = 1; l + i - 1 < r - i + 1; ++i)
        std::swap(s[l + i - 1], s[r - i + 1]);
    return ans;
}
bool judge(int l, int r) {
    int mid = (1 + n) >> 1;
    auto vl = hashS(1, mid, l, r),
         vr = hashT(1, mid, n - r + 1, n - l + 1);
    //    printf("%d %d\n", vl.val, vr.val);

    return vl == vr && brute_judge(l, r);
}

int main() {
    //    freopen("in", "r", stdin);
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; ++i) t[i] = s[n - i + 1];
    base[0] = 1;
    for (int i = 1; i <= n; ++i) base[i] = (ll)base[i - 1] * seed % mod;
    ubase[0] = 1;
    for (int i = 1; i <= n; ++i) ubase[i] = ubase[i - 1] * useed;

    hashS.init(s);
    hashT.init(t);

    int l = 1, r = n;
    while (l <= r && s[l] == s[r]) ++l, --r;
    if (l > r) {
        printf("%d %d\n", 1, n);
        return 0;
    }
    for (int i = l + 1; i < r; ++i)
        if (judge(l, i)) {
            printf("%d %d\n", l, i);
            return 0;
        }
    for (int i = r - 1; i > l; --i)
        if (judge(i, r)) {
            printf("%d %d\n", i, r);
            return 0;
        }
    puts("-1 -1");
}