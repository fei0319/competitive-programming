#include <bits/stdc++.h>

using ll = long long int;

void solve() {
	int n;
	std::cin >> n;
	
	std::vector<int> a(n * (n + 1) / 2 - 1);
	for (int &i : a) {
		std::cin >> i;
	}
	
	ll sum = std::accumulate(a.begin(), a.end(), 0);
	
	std::map<int, int> cnt;
	for (int i : a) {
		cnt[i] += 1;
	}
	
	std::set<int> odds;
	std::map<int, int> evens;
	for (auto [k, v] : cnt) {
		if (v & 1) {
			odds.insert(k);
			if (v - 1 > 0) {
				evens[k] = v - 1;
			}
		}
		else evens[k] = v;
	}
	
	auto calc = [&](int p) -> int {
		std::vector<int> tmp{odds.begin(), odds.end()};
        tmp.insert(tmp.begin() + p, 0);

        for (int i = tmp.size() - 1; i - 1 >= 0; --i) {
            tmp[i] -= tmp[i - 1];
        }
        for (int i = (n % 2 == 1); i < tmp.size(); ++i) {
            if (tmp[i] % 2 == 1) {
                return false;
            }
            tmp[i] /= 2;
        }

        std::vector<int> ans;
        for (int i = tmp.size() - 1; i >= (n % 2 == 1); --i) {
            ans.push_back(tmp[i]);
        }
        for (int i : tmp) {
            ans.push_back(i);
        }
        
        
        return -1;
	};
	
	auto check = [&]() -> bool {
		std::vector<int> tmp{odds.begin(), odds.end()};
		for (int i = tmp.size() - 1; i - 1 >= 0; --i) {
			tmp[i] -= tmp[i - 1];
		}
		for (int i = (n % 2 == 1); i < tmp.size(); ++i) {
			if (tmp[i] % 2 == 1) {
				return false;
			}
			tmp[i] /= 2;
		}
		
		std::vector<int> ans;
		for (int i = tmp.size() - 1; i >= (n % 2 == 1); --i) {
			ans.push_back(tmp[i]);
		}
		for (int i : tmp) {
			ans.push_back(i);
		}
		
		ll res = 0;
		for (int i = 0; i < ans.size(); ++i) {
			res += ll(i + 1) * (n - i) * ans[i];
		}
		
		if (res != sum) {
			return false;
		}
		
		for (int i = 0; i < n; ++i) {
			std::cout << ans[i] << ' ';
		}
		std::cout << '\n';
		return true;
	};
	
	
	
	if (odds.size() < (n + 1) / 2) {	
		for (int i = 0; i < (n + 1) / 2; ++i) {
			int v = calc(i);
			if (v != -1) {
				odds.insert(v);
				sum += v;
				
				if (check()) {
					return;
				}
				
				sum -= v;
				odds.erase(v);
			}
		}
	} else {
		std::vector<int> odd_vals{odds.begin(), odds.end()};
		
		for (int val : odd_vals) {
			odds.erase(val);
			evens[val] += 2;
			sum += val;
			
			if (check()) {
				return;
			}
			
			sum -= val;
			evens[val] -= 2;
			odds.insert(val);
		}
	}
	
	assert(false);
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