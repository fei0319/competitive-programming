#include <bits/stdc++.h>

int main() {
f:
    for (__int128 i = 0; i <= (int)4e8; ++i) {
        if (i == i + 1) {
            goto f;
        }
    }
}