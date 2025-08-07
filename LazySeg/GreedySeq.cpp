
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int maxn = 1e6 + 5;
int st[4 * maxn], lazy[4 * maxn];
vector<int> g[maxn];

void down(int id){
    if(lazy[id]){
        lazy[id * 2] += lazy[id];
        lazy[id * 2 + 1] += lazy[id];
        st[id * 2] += lazy[id];
        st[id * 2 + 1] += lazy[id];
        lazy[id] = 0;
    }
}

void update(int id, int l, int r, int u, int v, int val){
    if(v < l || r < u) return;
    if(u <= l && r <= v){
        st[id] += val;
        lazy[id] += val;
        return;
    }
    down(id);
    int mid = (l + r) / 2;
    update(id * 2, l, mid, u, v, val);
    update(id * 2 + 1, mid + 1, r, u, v, val);
    st[id] = max(st[id * 2], st[id * 2 + 1]);
}

int tin[maxn], out[maxn], timeDfs = 0;
void dfs(int u){
    tin[u] = ++timeDfs;
    for(int v: g[u]) dfs(v);
    out[u] = timeDfs;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n, k; cin >> n >> k;
    vector<int> a(n + 2, 1e9);
    for(int i = 1; i <= n; i++) cin >> a[i];

    stack<int> s;
    s.push(n + 1);

    for(int i = n; i >= 1; i--){
        while(s.size() && a[s.top()] <= a[i]) s.pop();
        g[s.top()].push_back(i);
        s.push(i);
    }

    dfs(n + 1);

    for(int i = 1; i <= k; i++) update(1, 1, n + 1, tin[i], out[i], 1);
    cout << st[1] << " ";
    for(int i = k + 1; i <= n; i++){
        update(1, 1, n + 1, tin[i - k], out[i - k], -1);
        update(1, 1, n + 1, tin[i], out[i], 1);
        cout << st[1] << " ";
    }
}
