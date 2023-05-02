#include <algorithm>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <vector>

int n;
std::vector<std::string> all;
std::string ans;
std::mt19937 eng(std::time(0));

void dfs(int n, std::string s) {
    if (n == 0) {
        all.push_back(s);
        return;
    }
    dfs(n - 1, s + 'T');
    dfs(n - 1, s + 'F');
}

int main() {
    std::scanf("%d", &n), ans.resize(n, 'T');
    dfs(3, "");
    int ptr = 0;
    while (ptr + 3 <= n) {
        shuffle(all.begin(), all.end(), eng);
        for (int i = 0; i < 5; ++i)
            std::cout << all[i] << std::endl;
    }
}