#include <bits/stdc++.h>

using ll = long long int;

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;
    
    std::vector<int> a(n);
    for (int &i : a) std::cin >> i;
    std::sort(a.begin(), a.end());
    
    int max_cnt = 0;
    for (int l = 0, r; l < n; l = r + 1) {
    	r = l;
    	while (r + 1 < n && a[r + 1] == a[r]) ++r;
    	if (r - l + 1 > max_cnt) {
    		max_cnt = r - l + 1;
    	}
    }
    std::vector<int> M;
    for (int l = 0, r; l < n; l = r + 1) {
    	r = l;
    	while (r + 1 < n && a[r + 1] == a[r]) ++r;
    	if (r - l + 1 == max_cnt) {
    		M.push_back(a[r]);
    	}
    }
    std::sort(M.begin(), M.end());
    int val = 0;
    for (int i = 1; i < M.size(); ++i) {
    	val = std::max(val, M[i] - M[i - 1]);
    }
    
    ll ans = std::max<ll>(M.front() - M.back() + ll(n - max_cnt) * k, val + ll(n - max_cnt - 1) * k);
	std::cout << ans << '\n';
    return 0;
}