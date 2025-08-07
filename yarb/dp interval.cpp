// Consider a string of length 
// N consisting of 0 and 1. The score for the string is calculated as follows:

//  ai  is added to the score if the string contains 1 at least once between li, ri Find the maximum possible score of a string.

#include<bits/stdc++.h>
#define ll long long
#define nl "\n"
#define all(v) v.begin(),v.end()
#define baraa ios_base::sync_with_stdio(false);cin.tie(NULL);
using namespace std;

struct segtree {
    vector<ll> tree, lazy;
    ll sz;

    segtree(ll n) {
        sz = n;
        tree = lazy = vector<ll>(4 * n, 0);
    }

    void chk(ll i, ll l, ll r) {
        if (lazy[i] != 0 && l != r) {
            propagate(i * 2, l, (l + r) / 2, lazy[i]);
            propagate(i * 2 + 1, (l + r) / 2 + 1, r, lazy[i]);
            lazy[i] = 0;
        }
    }

    void propagate(ll i, ll l, ll r, ll val) {
        lazy[i] += val;
        tree[i] += val;
    }

    ll get(ll i, ll l, ll r, ll ql, ll qr) {
        chk(i, l, r);
        if (l >= ql && qr >= r) return tree[i];
        if (ql > r || qr < l) return 0;
        ll leftSum = get(i * 2, l, (l + r) / 2, ql, qr);
        ll rightSum = get(i * 2 + 1, (l + r) / 2 + 1, r, ql, qr);
        return max(leftSum, rightSum);
    }

    void update(ll i,ll l,ll r,ll idx, ll val) {
        chk(i, l, r);
        if (l == r) {
            tree[i] += val;
            return;
        }
        if (idx <= (l + r) / 2)update(i * 2, l, (l + r) / 2, idx, val);
        else update(i * 2 + 1, (l + r) / 2 + 1, r, idx, val);
        tree[i] = max(tree[i * 2], tree[i * 2 + 1]);
    }

    void update(ll i, ll l, ll r, ll ql, ll qr, ll val) {
        chk(i, l, r);
        if (l >= ql && qr >= r) {
            propagate(i, l, r, val);
            return;
        }
        if (ql > r || qr < l) return;
        update(i * 2, l, (l + r) / 2, ql, qr, val);
        update(i * 2 + 1, (l + r) / 2 + 1, r, ql, qr, val);
        tree[i] = max(tree[i * 2], tree[i * 2 + 1]);
    }

    ll get(ll l, ll r) {
        return get(1, 0, sz - 1, l, r);
    }

    void update(ll l, ll r, ll val) {
        update(1, 0, sz - 1, l, r, val);
    }

    void update(ll idx, ll val) {
        update(1, 0, sz - 1, idx, val);
    }
};

int main() {
    baraa
    ll n, m;
    cin >> n >> m;
    vector<array<ll, 2> > ins[n], del[n + 1];
    for (ll i = 0; i < m; i++) {
        ll l, r, x;
        cin >> l >> r >> x;
        l--, r--;
        ins[l].push_back({x, r});
        del[r].push_back({x, l});
    }
    vector<ll> dp(n, -1e16);
    segtree seg(n);
    for (ll i = 0; i < n; i++) {
        dp[i] = seg.get(0, i - 1);
        // cout << dp[i] << ' ';
        seg.update(i, dp[i]);
        for (auto [x, l]: del[i])
            seg.update(l, i, x);
    }
    cout << max(0LL, seg.get(0, n - 1));
    return 0;
}
