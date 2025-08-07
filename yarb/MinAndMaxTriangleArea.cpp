#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Point {
    ll x, y;

    bool operator<(Point const &o) const {
        return x < o.x || (x == o.x && y < o.y);
    }
};

ll cross(const Point &a, const Point &b, const Point &c) {
    return (b.x - a.x) * (c.y - a.y)
           - (b.y - a.y) * (c.x - a.x);
}

// Andrew’s monotone chain: builds CCW hull with no colinear interior pts
vector<Point> convex_hull(vector<Point> &pts) {
    sort(pts.begin(), pts.end());
    int M = pts.size();
    if (M < 3) return pts;
    vector<Point> lo, hi;
    for (auto &p: pts) {
        while (lo.size() >= 2 &&
               cross(lo[lo.size() - 2], lo.back(), p) <= 0)
            lo.pop_back();
        lo.push_back(p);
    }
    for (int i = M - 1; i >= 0; --i) {
        while (hi.size() >= 2 &&
               cross(hi[hi.size() - 2], hi.back(), pts[i]) <= 0)
            hi.pop_back();
        hi.push_back(pts[i]);
    }
    lo.pop_back();
    hi.pop_back();
    lo.insert(lo.end(), hi.begin(), hi.end());
    return lo;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> M;
    vector<Point> pts(M);
    for (int i = 0; i < M; i++)
        cin >> pts[i].x >> pts[i].y;

    auto A = convex_hull(pts);
    int n = A.size();
    if (n < 3) {
        cout << "0\n";
        return 0;
    }
    if (n == 3) {
        // compute the single triangle's area
        ll a2 = llabs(cross(A[0], A[1], A[2]));
        ll area = a2 ;
        cout << area ;
        return 0;
    }
    auto area2 = [&](int i, int j, int k) {
        return llabs(cross(A[i], A[j], A[k]));
    };

    // 2) Maximum‐area rotating-calipers (O(n))
    ll bestMax2 = 0;
    int j = 1, k = 2;
    for (int i = 0; i < n; i++) {
        j = max(j, i + 1);
        k = max(k, j + 1);
        while (j < i + n && k < i + n) {
            int jj = j % n;
            int kk = k % n;
            int kk1 = (kk + 1) % n;
            ll cur = area2(i, jj, kk);
            ll nxt = area2(i, jj, kk1);
            if (nxt > cur) {
                k++;
            } else {
                bestMax2 = max(bestMax2, cur);
                j++;
            }
        }
    }

    // 3) Minimum‐area non-degenerate triangle (O(n))
    const ll INF = LLONG_MAX;
    ll bestMin2 = INF;
    for (int i = 0; i < n; i++) {
        int ip = (i + 1) % n;
        // always start k at least i+2
        int kk_idx = i + 2;
        // advance until local minimum
        while (true) {
            int k0 = kk_idx % n;
            int k1 = (kk_idx + 1) % n;
            ll cur = area2(i, ip, k0);
            ll nxt = area2(i, ip, k1);
            if (nxt < cur) {
                kk_idx++;
            } else {
                // only accept strictly positive areas
                if (cur > 0)
                    bestMin2 = min(bestMin2, cur);
                break;
            }
        }
    }

    cout << bestMin2 << "\n";
    return 0;
}
