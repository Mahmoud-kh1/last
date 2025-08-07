
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static const ll MOD = 998244353;

struct SegTree {
    int n;
    vector<ll> sum, mul, add;
    SegTree(int _n): n(_n) {
        sum .assign(4*n, 0);
        mul .assign(4*n, 1);   // multiplicative lazy = 1
        add .assign(4*n, 0);   // additive lazy = 0
    }
    // apply affine (b,c) to node covering length len:
    void apply(int o, int L, int R, ll b, ll c) {
        sum[o] = ( (sum[o]*b) % MOD
                 + (c * (R-L) ) % MOD ) % MOD;
        mul[o] = (mul[o]*b) % MOD;
        add[o] = (add[o]*b + c) % MOD;
    }
    void push(int o, int L, int R) {
        if (mul[o]!=1 || add[o]!=0) {
            int M = (L+R)/2;
            apply(o<<1,   L,   M, mul[o], add[o]);
            apply(o<<1|1, M,   R, mul[o], add[o]);
            mul[o]=1;  add[o]=0;
        }
    }
    void pull(int o) {
        sum[o] = (sum[o<<1] + sum[o<<1|1]) % MOD;
    }
    void build(int o, int L, int R, const vector<ll>& A) {
        if (R-L==1) {
            sum[o] = A[L] % MOD;
        } else {
            int M = (L+R)/2;
            build(o<<1,   L, M, A);
            build(o<<1|1, M, R, A);
            pull(o);
        }
    }
    // range [l,r): apply a_i = b*a_i + c
    void update(int o, int L, int R, int l, int r, ll b, ll c) {
        if (r<=L || R<=l) return;
        if (l<=L && R<=r) {
            apply(o,L,R,b,c);
            return;
        }
        push(o,L,R);
        int M = (L+R)/2;
        update(o<<1,   L,   M, l,r,b,c);
        update(o<<1|1, M,   R, l,r,b,c);
        pull(o);
    }
    // query sum over [l,r)
    ll query(int o, int L, int R, int l, int r) {
        if (r<=L || R<=l) return 0;
        if (l<=L && R<=r) return sum[o];
        push(o,L,R);
        int M = (L+R)/2;
        return ( query(o<<1,   L,   M, l,r)
               + query(o<<1|1, M,   R, l,r) ) % MOD;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    vector<ll> A(N);
    for(int i=0;i<N;i++){
        cin >> A[i];
    }

    SegTree st(N);
    st.build(1, 0, N, A);

    while(Q--){
        int type, l, r;
        cin >> type >> l >> r;
        if (type==0) {
            ll b, c;
            cin >> b >> c;
            // apply a_i = b*a_i + c for i in [l, r)
            st.update(1, 0, N, l, r, b%MOD, c%MOD);
        } else {
            // sum over [l,r)
            ll ans = st.query(1, 0, N, l, r);
            cout << ans << "\n";
        }
    }
    return 0;
}
