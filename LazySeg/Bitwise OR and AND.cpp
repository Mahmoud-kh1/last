#include <bits/stdc++.h>
using namespace std;
using ll = unsigned int;   // we only need up to 2^30; 32-bit unsigned is enough

struct SegTree {
    int n;
    vector<ll> tree, lazy;
    SegTree(int _n): n(_n) {
        tree .assign(4*n, 0);
        lazy .assign(4*n, 0);
    }
    // apply OR=v to node o covering [L,R)
    void apply(int o, ll v) {
        // every element in this segment gets OR=v,
        // so the AND of the segment also gets OR=v
        tree[o] |= v;
        // record that children need to be OR-ed by v later
        lazy[o] |= v;
    }
    // push the lazy tag down
    void push(int o) {
        if (lazy[o]) {
            apply(o<<1,   lazy[o]);
            apply(o<<1|1, lazy[o]);
            lazy[o] = 0;
        }
    }
    // pull children up
    void pull(int o) {
        tree[o] = tree[o<<1] & tree[o<<1|1];
    }
    // range‐update [l,r): OR=v
    void update(int o, int L, int R, int l, int r, ll v) {
        if (r<=L || R<=l) return;
        if (l<=L && R<=r) {
            apply(o, v);
            return;
        }
        push(o);
        int M = (L+R)>>1;
        update(o<<1,   L,   M, l, r, v);
        update(o<<1|1, M,   R, l, r, v);
        pull(o);
    }
    // range‐query [l,r): AND
    ll query(int o, int L, int R, int l, int r) {
        if (r<=L || R<=l) return ~0u; // all‐1s for unsigned 32
        if (l<=L && R<=r) return tree[o];
        push(o);
        int M = (L+R)>>1;
        return query(o<<1,   L,   M, l, r)
             & query(o<<1|1, M,   R, l, r);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    SegTree st(n);

    while(m--){
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 1) {
            unsigned int v;
            cin >> v;
            st.update(1, 0, n, l, r, v);
        } else {
            // type==2
            unsigned int ans = st.query(1, 0, n, l, r);
            cout << ans << "\n";
        }
    }
    return 0;
}
