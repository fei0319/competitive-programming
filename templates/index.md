# Secret Sealing Club 模板 F

定义执行一次以下代码花费的时间为一个标准时间。其在各个 OJ 上的具体值为：

- Codeforces: 202ms
- AtCoder: 221ms
- LibraryChecker: 176ms

```cpp
constexpr u64 N = 1e6;
u64 res = 0;
for (u64 i = 0; i < N; ++i) {
    res += i * i;
}
```
