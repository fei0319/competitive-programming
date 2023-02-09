#include <bits/stdc++.h>

using i64 = long long int;

constexpr int MOD = 998244353;

template <typename Tp>
Tp qpow(Tp a, int b){
	Tp res = 1;
	while(b){
		if(b & 1) res *= a;
		a *= a, b >>= 1;
	}
	return res;
}

int norm(int x) {
    if (x < 0) {
        x += MOD;
    }
    if (x >= MOD){
        x -= MOD;
    }
    return x;
}

struct Z {
    int x;
    Z(int x = 0) : x(norm(x)) {}
    Z(i64 x) : x(norm(x % MOD)) {}
    int val() const {
        return x;
    }
    Z operator-() const {
        return Z(norm(MOD - x));
    }
    Z inv() const {
        assert(x != 0);
        return qpow(*this, MOD - 2);
    }
    Z &operator*=(const Z &rhs) {
        x = i64(x) * rhs.x % MOD;
        return *this;
    }
    Z &operator+=(const Z &rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    Z &operator-=(const Z &rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    Z &operator/=(const Z &rhs) {
        return *this *= rhs.inv();
    }
    friend Z operator*(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res *= rhs;
        return res;
    }
    friend Z operator+(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res += rhs;
        return res;
    }
    friend Z operator-(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res -= rhs;
        return res;
    }
    friend Z operator/(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res /= rhs;
        return res;
    }
    friend std::istream &operator>>(std::istream &is, Z &a) {
        i64 v;
        is >> v;
        a = Z(v);
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const Z &a) {
        return os << a.val();
    }
};

constexpr int maxn = 2e5 + 19;
int n, a[maxn];

void solve(void){
	std::cin >> n;
	for(int i = 1; i <= n; ++i) std::cin >> a[i];
	
	std::sort(a + 1, a + 1 + n);
	int last = 0;
	i64 ans = 0;
	for(int i = 1; i <= n; ++i){
		if(a[i] > last + 1){
			ans += a[i] - last - 1;
			a[i] = last + 1;
			++last;
		}else if(a[i] == last + 1){
			++last;
		}
	}
	std::cout << ans << '\n';
}

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	int T;
	std::cin >> T;
	
	while(T--){
		solve();
	}
	
	return 0;
}