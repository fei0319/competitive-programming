#include <bits/stdc++.h>

using ll = long long int;
const int MOD = 998244353;
const int N = 1e5;

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = (ll)res * a % MOD;
        a = (ll)a * a % MOD, b >>= 1;
    }
    return res;
}
int fact[N + 1], ifact[N + 1];
int binom(int n, int m) {
	if (n == m) return 1;
	if (n < m) return 0;
	if (m < 0) return 0;
    return (ll)fact[n] * ifact[n - m] % MOD * ifact[m] % MOD;
}

void add(int &x, int y) {
	x = (x + y) % MOD;
}

void solve() {
    int n;
    std::cin >> n;

    int z = 0;
    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        int t;
        std::cin >> t;
        if (t < 0) a[-t - 1] += 1;
        else if (t > 0) b[t - 1] += 1;
        else ++z;
    }
    while (!a.empty() && !a.back()) a.pop_back();
    while (!b.empty() && !b.back()) b.pop_back();

    auto F = [](std::vector<int> a, int slot, bool extra) {
        std::unordered_map<int, int> f;
        int val = 0;
        
        if (extra) {
        	val = 1;
        } else {
        	f[slot] = 1;
        }
        
        for (int i : a) {
        	if (val == 0) slot = 0;
        	
        	std::unordered_map<int, int> g;
        	
        	for (auto [s, v] : f) {
        		int v_to_add = (ll)v * binom(i - 1, s - 1) % MOD;
        		if (v_to_add) {
        			add(g[i - s], v_to_add);
        		}
        	}
        	
        	int v_to_add = (ll)val * binom(i - 1, slot - 1) % MOD;
        	if (v_to_add) {
        		add(g[i - slot], v_to_add);
        	}
        	f.swap(g);
        	
        	int n_val = 0;
        	if (val && i >= slot + 1) {
        		n_val = (ll)val * binom(i - 1, slot) % MOD;
        	}
        	slot = i - slot - 1;
        	val = n_val;
        }
        
        int res = ((slot == 0 ? val : 0) + f[0]) % MOD;
        return res;
    };

    int ans = 0;
    for (int i = 0; i <= z; ++i) {
        ans = (ans + (ll)binom(z, i) * F(a, i, 1) * F(b, z - i, 0)) % MOD;
        ans = (ans + (ll)binom(z, i) * F(a, i, 0) * F(b, z - i, 1)) % MOD;
        ans = (ans - (ll)binom(z, i) * F(a, i, 0) * F(b, z - i, 0)) % MOD;
    }
    ans = (ans + MOD) % MOD;
    std::cout << ans << '\n';
}

int main() {
    fact[0] = 1;
    for (int i = 1; i <= N; ++i) fact[i] = (ll)fact[i - 1] * i % MOD;
    ifact[N] = qpow(fact[N], MOD - 2);
    for (int i = N - 1; i >= 0; --i) ifact[i] = (ll)ifact[i + 1] * (i + 1) % MOD; 
    
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) solve();
}