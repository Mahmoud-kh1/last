#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ull unsigned long long
int n;
const int mod = 1e9 + 7;
const int N = 4e5;
pair<int, ull> T[4 * N];
pair<int, ull> lazy[4 * N];
vector<int> pr;

int bpow(int a, int b)
{
    int res = 1;
    while (b) {
        if (b & 1)
            res = 1ll * res * a % mod;
        a = 1ll * a * a % mod;
        b >>= 1;
    }
    return res;
}

int inv(int a)
{
    return bpow(a, mod - 2);
}

int mmul(int a, int b)
{
    return 1ll * a * b % mod;
}

int mdiv(int a, int b)
{
    return mmul(a, inv(b));
}

void build(int u = 1, int l = 0, int r = n - 1)
{
    if (l == r) {
        lazy[u] = { 1, 0 };
        T[u] = { 1, 0 };
        return;
    }
    int mid = (l + r) / 2;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    lazy[u] = { 1, 0 };
    T[u] = { 1, 0 };
}

void push(int u, int l, int r)
{
    auto [p, m] = lazy[u];
    if (p != 1 || m != 0) {
        T[u].first = 1ll * T[u].first * bpow(p, r - l + 1) % mod;
        T[u].second |= m;
        if (l != r) {
            lazy[u << 1].first = 1ll * lazy[u << 1].first * p % mod;
            lazy[u << 1].second |= m;
            lazy[u << 1 | 1].first = 1ll * lazy[u << 1 | 1].first * p % mod;
            lazy[u << 1 | 1].second |= m;
        }
        lazy[u] = { 1, 0 };
    }
}

void update(int lq, int rq, ull mask, int x, int u = 1, int l = 0, int r = n - 1)
{
    if (r < lq || l > rq)
        return;
    if (lq <= l && r <= rq) {
        lazy[u].first = 1ll * lazy[u].first * x % mod;
        lazy[u].second |= mask;
        push(u, l, r);
        return;
    }
    push(u, l, r);
    int mid = (l + r) / 2;
    update(lq, rq, mask, x, u << 1, l, mid);
    update(lq, rq, mask, x, u << 1 | 1, mid + 1, r);
    push(u << 1, l, mid);
    push(u << 1 | 1, mid + 1, r);
    T[u].first = 1ll * T[u << 1].first * T[u << 1 | 1].first % mod;
    T[u].second = T[u << 1].second | T[u << 1 | 1].second;
}

pair<int, ull> query(int lq, int rq, int u = 1, int l = 0, int r = n - 1)
{
    push(u, l, r);
    if (r < lq || l > rq)
        return { 1, 0 };
    if (lq <= l && r <= rq)
        return T[u];
    int mid = (l + r) / 2;
    auto [p1, m1] = query(lq, rq, u << 1, l, mid);
    auto [p2, m2] = query(lq, rq, u << 1 | 1, mid + 1, r);
    return { 1ll * p1 * p2 % mod, m1 | m2 };
}

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    vector<bool> isPrime(301, true);
    for (int i = 2; i <= 300; ++i) {
        if (isPrime[i]) {
            pr.push_back(i);
            for (int j = i * 2; j <= 300; j += i)
                isPrime[j] = false;
        }
    }

    ull mask_arr[301] = {};
    for (int x = 1; x <= 300; ++x) {
        int temp = x;
        for (int i = 0; i < pr.size(); ++i) {
            while (temp % pr[i] == 0) {
                temp /= pr[i];
                mask_arr[x] |= 1ull << i;
            }
        }
    }

    auto num = [&](ull mask) {
        int res = 1;
        for (int p = 0; p < pr.size(); ++p) {
            if (mask & (1ull << p)) {
                res = mmul(res, mdiv(pr[p] - 1, pr[p]));
            }
        }
        return res;
    };

    int q;
    cin >> n >> q;
    build();
    int a[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        update(i, i, mask_arr[a[i]], a[i]);
    }

    while (q--) {
        string s;
        cin >> s;
        if (s == "TOTIENT") {
            int l, r;
            cin >> l >> r;
            auto [p, m] = query(l - 1, r - 1);
            cout << 1ll * p * num(m) % mod << endl;
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            update(l - 1, r - 1, mask_arr[x], x);
        }
    }
}
