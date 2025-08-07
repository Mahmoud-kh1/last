#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static const int MOD = 4001;
static const int MAXB = 11;  // bits needed up to 2^10=1024

struct Node {
    int cnt[MAXB];
    int lazyMask;
    Node() {
        memset(cnt, 0, sizeof(cnt));
        lazyMask = 0;
    }
};

struct SegTree {
    int n;
    vector<Node> st;
    SegTree(int _n): n(_n), st(4*_n) {}

    // apply XOR mask m to node o covering length len
    void apply(int o, int len, int m) {
        for (int k = 0; k < MAXB; k++) {
            if ((m >> k) & 1) {
                st[o].cnt[k] = len - st[o].cnt[k];
            }
        }
        st[o].lazyMask ^= m;
    }

    void push(int o, int L, int R) {
        int m = st[o].lazyMask;
        if (!m) return;
        int M = (L+R)>>1;
        apply(o<<1,   M - L + 1, m);
        apply(o<<1|1, R - (M+1) + 1, m);
        st[o].lazyMask = 0;
    }

    void pull(int o) {
        for (int k = 0; k < MAXB; k++) {
            st[o].cnt[k] = st[o<<1].cnt[k] + st[o<<1|1].cnt[k];
        }
    }

    // build from initial X array[0..n]
    void build(int o, int L, int R, const vector<int>& X) {
        if (L == R) {
            for (int k = 0; k < MAXB; k++) {
                st[o].cnt[k] = (X[L] >> k) & 1;
            }
        } else {
            int M = (L+R)>>1;
            build(o<<1,   L,   M, X);
            build(o<<1|1, M+1, R, X);
            pull(o);
        }
    }

    // range XOR update [ql..qr] ^= m
    void update(int o, int L, int R, int ql, int qr, int m) {
        if (qr < L || R < ql) return;
        if (ql <= L && R <= qr) {
            apply(o, R - L + 1, m);
            return;
        }
        push(o, L, R);
        int M = (L+R)>>1;
        update(o<<1,   L,   M, ql, qr, m);
        update(o<<1|1, M+1, R, ql, qr, m);
        pull(o);
    }

    // query counts on [ql..qr], accumulate into cntOut[k]
    void query(int o, int L, int R, int ql, int qr, int cntOut[]) {
        if (qr < L || R < ql) return;
        if (ql <= L && R <= qr) {
            for (int k = 0; k < MAXB; k++) {
                cntOut[k] += st[o].cnt[k];
            }
            return;
        }
        push(o, L, R);
        int M = (L+R)>>1;
        query(o<<1,   L,   M, ql, qr, cntOut);
        query(o<<1|1, M+1, R, ql, qr, cntOut);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> A(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }

    // build prefix‐xor array X[0..n]
    vector<int> X(n+1);
    X[0] = 0;
    for (int i = 1; i <= n; i++) {
        X[i] = X[i-1] ^ A[i];
    }

    SegTree st(n+1);
    st.build(1, 0, n, X);

    // precompute 2^k % 4001
    int pow2[MAXB];
    pow2[0] = 1;
    for (int k = 1; k < MAXB; k++) {
        pow2[k] = (pow2[k-1] * 2) % MOD;
    }

    while (m--) {
        int type;
        cin >> type;
        if (type == 1) {
            int p, x;
            cin >> p >> x;
            int delta = A[p] ^ x;
            A[p] = x;
            if (delta) {
                st.update(1, 0, n, p, n, delta);
            }
        } else {
            int a, b;
            cin >> a >> b;
            int cnt1[MAXB] = {};
            // we need X[a-1..b]
            st.query(1, 0, n, a-1, b, cnt1);
            int msize = (b - (a - 1) + 1);
            int ans = 0;
            for (int k = 0; k < MAXB; k++) {
                int c1 = cnt1[k];
                int c0 = msize - c1;
                // contribution = 2^k * c1 * c0
                ans = (ans + (ll)pow2[k] * c1 % MOD * c0) % MOD;
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
