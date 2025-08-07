// you have a tree and each value have a[i], b[i], the query is u, you need to count how many ways if for each node we chose only one a[i] or b[i] so the product of them is prefect square ,
// a[i], b[i] <= 1000

#include <bits/stdc++.h>
#define int long long
#define ed '\n'
using namespace std;

#define ll long long 
// M is number of prime until max(a[i], b[i])
constexpr int N = 1e4 + 4, M = 170, mod = 998244353;
using mask = bitset<M>;

ll mul(ll F, ll S) { return F % mod * (S % mod) % mod; }

ll binpow(ll b, ll p) {
    b %= mod;
    ll res = 1;
    while (p) {
        if (p & 1) res = mul(res, b);
        p >>= 1, b = mul(b, b);
    }
    return res;
}

template<typename T = mask, int B = M>
struct Basis {
    T a[B];
    int sz{}, n{};

    Basis() {
        sz = n = 0;
        for (int i = 0;i < B;i++)
            a[i] = 0;
    }

    bool all_zeros(bitset<170> &x) {
        bool f = 1;
        for (int i = 0; i < x.size(); i++)
            if (x[i])f = 0;

        return f;
    }

    void insert(T x) {
        for (int i = B - 1; i >= 0; i--) {
            if (x[i] == 0) continue;
            if (a[i] == 0) {
                a[i] = x;
                sz++;
                return;
            }
            x ^= a[i];
        }
        ++n;
    }

    bool can(T x) {
        for (int i = B - 1; i >= 0; i--) {
            if (a[i] != 0 && x[i] == 1)
                x ^= a[i];
        }
        return x == 0;
    }

    int count_xors(T x) {
        return (can(x) ? binpow(2, n - sz) % mod : 0);
    }

    // T max_xor(T ans = 0) {
    //     for (int i = B - 1; i >= 0; i--) {
    //         ans = max(ans, ans ^ a[i]);
    //     }
    //     return ans;
    // }
};

int n;
vector<int> adj[N], spf(N), pos(N) ,ans(N);
vector<mask> a(N), b(N);

void sieve() {
    spf[1] = 1;
    int idx = 0;
    for (int i = 2;i < N;++i) {
        if (spf[i] == 0) {
            pos[i] = idx++;
            for (int j = i;j < N;j += i)
                spf[j] = i;
        }
    }
}

pair<Basis<mask, M>, mask> dfs0(int u, int p) {
    Basis<mask, M> me;
    me.insert(a[u] ^ b[u]);
    mask xor_a = a[u];
    for (auto v: adj[u]) {
        if (v == p) continue;
        auto [ch, chxor_a] = dfs0(v, u);
        if (ch.sz > me.sz) swap(ch, me);
        for (int k = 0; k < M; k++) {
            if (ch.a[k] != 0)
                me.insert(ch.a[k]);
        }
        me.n += ch.n;
        xor_a ^= chxor_a;
    }
    if (me.can(xor_a)) {
        // cout << xor_a.to_ullong() << ' ' << u << ' ' << me.n << ed;
        ans[u] = binpow(2, me.n);
    }
    return {me, xor_a};
}

void doWork(int TC) {
    sieve();
    cin >> n;
    for (int i = 1;i <= n;i++) {
        int x; cin >> x;
        while (x > 1) {
            a[i][pos[spf[x]]].flip();
            x /= spf[x];
        }
    }
    for (int i = 1;i <= n;i++) {
        int x; cin >> x;
        while (x > 1) {
            b[i][pos[spf[x]]].flip();
            x /= spf[x];
        }
    }
    for (int i = 2;i <= n;i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs0(1, 0);
    int q; cin >> q;
    while (q--) {
        int u; cin >> u;
        cout << ans[u] << ed;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int _ = 1;
    // cin >> _;
    for (int __ = 1; __ <= _; __++) {
        // cout << "Case " << __ << ":\n";
        doWork(__);
        // if (__ < _) cout << '\n';
        // cout << '\n';
    }
    return 0;
}
