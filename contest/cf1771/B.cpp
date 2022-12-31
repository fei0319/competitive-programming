#include <bits/stdc++.h>

int main(){
    int T;
    std::cin >> T;
    while(T--){
        int n, m;
        std::cin >> n >> m;
        std::vector<std::vector<int>> a(n + 1);
        for(int x, y, i = 0; i < m; ++i){
            std::cin >> x >> y;
            if(x > y) std::swap(x, y);
            a[x].push_back(y);
        }
        int lim = n;
        long long ans = 0ll;
        for(int i = n; i >= 1; --i){
            for(int j : a[i]) lim = std::min(lim, j - 1);
            ans += lim - i + 1;
        }
        std::cout << ans << std::endl;
    }
}