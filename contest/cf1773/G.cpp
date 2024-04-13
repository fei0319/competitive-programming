#include <bits/stdc++.h>

using ll = long long int;
using ld = long double;

constexpr int MAXN = 2e5 + 19;

template <typename It>
void fwt(It f, int l, int r) {
	if (l == r) {
		return;
	}
	int mid = (l + r) / 2;
	fwt(f, l, mid);
	fwt(f, mid + 1, r);
	for (int i = mid + 1; i <= r; ++i) {
		f[i] += f[i - (mid + 1) + l];
	}
}

template <typename It>
void ifwt(It f, int l, int r) {
	if (l == r) {
		return;
	}
	int mid = (l + r) / 2;
	for (int i = mid + 1; i <= r; ++i) {
		f[i] -= f[i - (mid + 1) + l];
	}
	ifwt(f, l, mid);
	ifwt(f, mid + 1, r);
}

int n, m;
int a[1 << 20], cnt[1 << 20];
void solve(std::vector<ld> &dp, int l, int r) {
	static ld f[MAXN];
	
	if (l == r) {
		return;
	}
	int mid = (l + r) / 2;
	solve(dp, l, mid);
	
	for (int i = l; i <= mid; ++i) {
		f[i] = dp[i] / (n - cnt[i]);
	}
	for (int i = mid + 1; i <= r; ++i) {
		f[i] = 0;
	}
	
	fwt(f, l, r);
	for (int i = l; i <= r; ++i) {
		f[i] *= a[i];
	}
	ifwt(f, l, r);
	for (int i = mid + 1; i <= r; ++i) {
		dp[i] += f[i];
	}
	
	solve(dp, mid + 1, r);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;

    m -= 1;
    int T = 1 << m;
    
    int g = 0;
    
    for (int i = 1; i <= n; ++i) {
        std::string s;
        std::cin >> s;
        int v = 0;
        for (int j = 1; j <= m; ++j) {
            if (s[j] == '1') {
                v |= 1 << (j - 1);
            }
        }
        if (s[0] == '1') {
            v ^= (1 << m) - 1;
            a[v] += 1;
            
            g |= v;
        }
        
        cnt[v] += 1;
    }

    for (int s = T - 1; s >= 1; --s) {
    	if (cnt[s] && (s & g) != s) {
    		std::cout << "0\n";
    		return 0;
    	}
    	for (int i = (s - 1) & s; ; i = (i - 1) & s) {
    		cnt[s] += cnt[i];
    		if (i == 0) {
    			break;
    		}
    	}
    }
    
    std::vector<ld> dp(T);
    dp[0] = 1;
    fwt(a, 0, T - 1);
    solve(dp, 0, T - 1);
    
    std::cout << std::fixed << std::setprecision(16);
    std::cout << dp[g] << '\n';

    return 0;
}