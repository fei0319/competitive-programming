#include <bits/stdc++.h>

using ll = long long int;

void solve(void) {
    int n;
    std::string s;
    std::cin >> n >> s;

    std::unordered_set<char> st;
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += st.size();
        st.insert(s[i]);
    }
    ans += st.size();

    std::cout << ans << '\n';
}

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}