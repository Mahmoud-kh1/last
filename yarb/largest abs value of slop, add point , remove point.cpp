#include <bits/stdc++.h>

using namespace std;

void fileIO(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
#ifdef ONLINE_JUDGE
/*        freopen("angle1.in ", "r", stdin);
        freopen("angle1.out ", "w", stdout);*/
#endif
}
void fastIO(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

typedef long long ll;
#define int ll

struct comp {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) const {
        return a.first * b.second > b.first * a.second;
    }
};
void solve(int tc) {

    int n, q; cin >> n >> q;

    multiset<pair<int, int>> ms;
    multiset<pair<int, int>, comp> slopes;

    auto add=[&](int x, int y) {
        ms.insert({x, y});
        auto it = ms.find({x, y});
        auto it2 = it;
        it2++;

        if(it != ms.begin()) {
            auto it1 = it;
            it1--;
            slopes.insert({abs(it->second - it1->second), abs(it->first - it1->first)});
            if(it2 != ms.end()) {
                slopes.erase(slopes.find({abs(it2->second - it1->second), abs(it2->first - it1->first)}));
            }
        }
        if(it2 != ms.end()) {
            slopes.insert({abs(it->second - it2->second), abs(it->first - it2->first)});
        }
    };

    auto remove=[&](int x, int y) {
        auto it = ms.find({x, y});
        auto it2 = it;
        it2++;

        if(it != ms.begin()) {
            auto it1 = it;
            it1--;
            slopes.erase(slopes.find({abs(it->second - it1->second), abs(it->first - it1->first)}));
            if(it2 != ms.end()) {
                slopes.insert({abs(it2->second - it1->second), abs(it2->first - it1->first)});
            }
        }
        if(it2 != ms.end()) {
            slopes.erase(slopes.find({abs(it->second - it2->second), abs(it->first - it2->first)}));
        }
        ms.erase(it);
    };

    auto ans=[&]() {
        if(slopes.empty()) {
            cout << -1 << "\n";
            return;
        }
        auto it = slopes.begin();
        int g = gcd(it->first, it->second);
        cout << it->first / g << " " << it->second / g << "\n";
    };

    for (int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        add(x, y);
    }

    ans();
    while (q--) {
        int op, x, y; cin >> op >> x >> y;
        if(op == 1)  add(x, y);
        else remove(x, y);
        ans();
    }
}

signed main() {

    fastIO(); fileIO();
    cout << setprecision(10) << fixed;
    int t = 1; //cin >> t;

    for (int i = 1; i <= t; ++i)
        solve(i);

    return 0;
}
