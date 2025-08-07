#include <bits/stdc++.h>
using namespace std;
 
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, char>>> in(n + 1), out(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v; 
        char c;
        cin >> u >> v >> c;
        in[v].push_back(make_pair(u, c));
        out[u].push_back(make_pair(v, c));
    }

    queue<pair<int, int>> q;
    vector<vector<int>> pal(n + 1, vector<int> (n + 1));
    for (int u = 1; u <= n; u++) {
        pal[u][u] = 1;
        q.push(make_pair(u, u));
    }

    for (int u = 1; u <= n; u++) {
        for (auto &[v, c] : out[u]) {
            if (!pal[u][v]) {
                pal[u][v] = 1;
                q.push(make_pair(u, v));
            }
        }
    }

    while(!q.empty()) {
        auto[u, v] = q.front();
        q.pop();

        for (auto &[v1, c1] : in[u]) {
            for (auto &[v2, c2] : out[v]) {
                if (c1 == c2 && pal[v1][v2] == 0) {
                    pal[v1][v2] = 1;
                    q.push(make_pair(v1, v2));
                }
            }
        }
    }

    long long ans = 0;
    for (int u = 1; u <= n; u++) {
        for (int v = 1; v <= n; v++) {
            if (u == v) continue;
            ans += pal[u][v];
        }
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
