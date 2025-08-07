#include <bits/stdc++.h>

using namespace std;

void fast() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

#define fr first
#define sc second
#define all(v) v.begin(), v.end()
#define mem(arr, value) memset(arr, value, sizeof(arr))
#define mid(l, r) (l + (r - l) / 2)
#define endl "\n"
#define int long long

const int N = 1e6 + 5;
const long long oo = LONG_LONG_MAX;
static const int M1 = 1000000021, B1 = 91138233;
static const int M2 = 1000000009, B2 = 97266353;
int MOD1 = M1, MOD2 = M2;
int pw1[N], pw2[N];

void build() {
    pw1[0] = pw2[0] = 1;
    for (int i = 1; i < N; i++) {
        pw1[i] = (pw1[i - 1] * B1) % MOD1;
        pw2[i] = (pw2[i - 1] * B2) % MOD2;
    }
}

struct RH {
    int n;
    vector<int> h1, p1, h2, p2;

    RH(const string &s) : n(s.size()), h1(n + 1), p1(n + 1), h2(n + 1), p2(n + 1) {
        p1[0] = p2[0] = 1;
        for (int i = 0; i < n; i++) {
            h1[i + 1] = (h1[i] * B1 + (s[i] - 'a' + 1)) % M1;
            p1[i + 1] = (p1[i] * B1) % M1;
            h2[i + 1] = (h2[i] * B2 + (s[i] - 'a' + 1)) % M2;
            p2[i + 1] = (p2[i] * B2) % M2;
        }
    }

    pair<int, int> get(int l, int r) {
        int x1 = (h1[r + 1] + M1 - (h1[l] * p1[r - l + 1]) % M1) % M1;
        int x2 = (h2[r + 1] + M2 - (h2[l] * p2[r - l + 1]) % M2) % M2;
        return {x1, x2};
    }
};

void solve() {
    int n;
    cin >> n;
    vector<string> str(n);
    for (auto &s: str) cin >> s;

    vector<tuple<int, int, int>> value(n);
    for (int i = 0; i < n; i++) {
        int h1 = 0, h2 = 0;
        for (char c: str[i]) {
            h1 = (h1 * B1 + (c - 'a' + 1)) % M1;
            h2 = (h2 * B2 + (c - 'a' + 1)) % M2;
        }
        value[i] = {h1, h2, (int) str[i].size()};
    }

    vector<tuple<pair<int, int>, int, int>> v;
    map<pair<int, int>, vector<pair<int, int>>> ma;
    for (int i = 0; i < n; i++) {
        auto [H11, H12, szA] = value[i];
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            auto [H21, H22, szB] = value[j];
            int nw1 = (H11 * pw1[szB] + H21) % MOD1;
            int nw2 = (H12 * pw2[szB] + H22) % MOD2;
            ma[{nw1, nw2}].push_back({i + 1, j + 1});
        }
    }
    for (auto [key, val]: ma) {
        for (int i = 0; i < val.size(); ++i) {
            for (int j = 0; j < val.size(); ++j) {
                if (i != j) {
                    int x1 = val[i].first, y1 = val[i].second;
                    int x2 = val[j].first, y2 = val[j].second;
                    set<int> st = {x1, y1, x2, y2};
                    if (st.size() == 4) {
                        cout << "YES" << endl;
                        cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << endl;
                        return;
                    }
                }
            }
        }
    }

    cout << "NO" << endl;
}

int32_t main() {
    fast();
    build();
    solve();
    return 0;
}
