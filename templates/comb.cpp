template <class Z>
struct Comb {
    std::vector<Z> fact_, ifact_;
    Comb(int n) : fact_(n), ifact_(n) {
        fact_[0] = 1;
        for (int i = 1; i < n; ++i) {
            fact_[i] = fact_[i - 1] * i;
        }
        ifact_[n - 1] = 1 / fact_[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            ifact_[i] = ifact_[i + 1] * (i + 1);
        }
    }
    Z fact(int x) {
        return fact_[x];
    }
    Z ifact(int x) {
        return ifact_[x];
    }
    Z binom(int n, int m) {
        return fact_[n] * ifact_[n - m] * ifact_[m];
    }
};
