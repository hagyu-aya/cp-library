constexpr int MAX_FACT = 4000000;
modint998244353 fact[MAX_FACT + 1] = {1};
modint998244353 inv[MAX_FACT + 1] = {1};

modint998244353 init_fact(int n) {
    for(int i = 1; i <= MAX_FACT; ++i){
        fact[i] = fact[i - 1] * i;
        inv[i] = fact[i].inv();
    }
}

modint998244353 nCk(int n, int k) {
    if(n < k) return 0;
    return fact[n] * inv[k] * inv[n-k];
}
