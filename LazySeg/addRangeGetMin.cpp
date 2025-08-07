#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct SegTree {
    int n;
    vector<ll> mn, lazy;
    SegTree(int _n): n(_n), mn(4*n, 0), lazy(4*n, 0) {}

    // push pending addition from node idx into its children
    void push(int idx) {
        if (lazy[idx] != 0) {
            ll v = lazy[idx];
            mn[idx*2]   += v;
            mn[idx*2+1] += v;
            lazy[idx*2] += v;
            lazy[idx*2+1] += v;
            lazy[idx] = 0;
        }
    }

    // pull children values up into node idx
    void pull(int idx) {
        mn[idx] = min(mn[idx*2], mn[idx*2+1]);
    }

    // add v to range [l..r] (inclusive) in the tree node covering [L..R]
    void update(int idx, int L, int R, int l, int r, ll v) {
        if (r < L || R < l) return;            // no overlap
        if (l <= L && R <= r) {               // fully covered
            mn[idx]   += v;
            lazy[idx] += v;
            return;
        }
        push(idx);
        int M = (L+R) >> 1;
        update(idx*2,   L,   M, l, r, v);
        update(idx*2+1, M+1, R, l, r, v);
        pull(idx);
    }

    // query min on [l..r] within node covering [L..R]
    ll query(int idx, int L, int R, int l, int r) {
        if (r < L || R < l) return LLONG_MAX; // no overlap
        if (l <= L && R <= r)                 // fully covered
            return mn[idx];
        push(idx);
        int M = (L+R) >> 1;
        return min(
            query(idx*2,   L,   M, l, r),
            query(idx*2+1, M+1, R, l, r)
        );
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    SegTree st(n);

    while (m--) {
        int type, l, r;
        cin >> type >> l >> r;
        if (type == 1) {
            ll v;
            cin >> v;
            // add v to [l..r-1], i.e. indices l..r-1
            st.update(1, 0, n-1, l, r-1, v);
        } else {
            // query min on [l..r-1]
            ll ans = st.query(1, 0, n-1, l, r-1);
            cout << ans << "\n";
        }
    }
    return 0;
}
