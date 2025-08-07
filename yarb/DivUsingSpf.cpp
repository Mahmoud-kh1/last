vector<int> build_spf(int max_n) {
    vector<int> spf(max_n + 1);
    iota(spf.begin(), spf.end(), 0);
    for (int i = 2; i * i <= max_n; ++i) {
        if (spf[i] == i) {
            for (int j = i * i; j <= max_n; j += i) {
                if (spf[j] == j) spf[j] = i;
            }
        }
    }
    return spf;
}
vector<int> get_divisors(int x, const vector<int>& spf) {
    vector<pair<int,int>> factors;
    while (x > 1) {
        int p = spf[x], cnt = 0;
        while (x % p == 0) {
            x /= p;
            ++cnt;
        }
        factors.emplace_back(p, cnt);
    }

    vector<int> divisors = {1};
    for (auto& [p, cnt] : factors) {
        int sz = divisors.size();
        int mul = 1;
        for (int e = 1; e <= cnt; ++e) {
            mul *= p;
            for (int i = 0; i < sz; ++i) {
                divisors.push_back(divisors[i] * mul);
            }
        }
    }

    divisors.erase(remove(divisors.begin(), divisors.end(), 1), divisors.end());
    return divisors;
}
