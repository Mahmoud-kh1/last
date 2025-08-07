You are given a set of integer numbers, initially it is empty. You should perform n queries.

There are three different types of queries:

1 l r — Add all missing numbers from the interval [l, r]
2 l r — Remove all present numbers from the interval [l, r]
3 l r — Invert the interval [l, r] — add all missing and remove all present numbers from the interval [l, r]
After each query you should output MEX of the set — the smallest positive (MEX  ≥ 1) integer number which is not presented in the set.

#include <bits/stdc++.h>
using namespace std;
void Yasser() {
    ios::sync_with_stdio(0);
    cin.tie(0);
}
const int N = 4e5 + 5 ;
struct LazyPropagation {
    #define LF (2 * x + 1)
    #define RT (2 * x + 2)
    #define md ((lx + rx)/2)

    vector<int> segment ;
    vector<int> lazy ;

    LazyPropagation (){
        segment.resize(N * 4 , 0) ;
        lazy.resize(4 * N , -1) ;
    }
    // lazy[x] == 1 -> add
    // lazy[x] == 2 -> remove
    // lazy[x] == 3 -> invert
    void propagate (int x, int lx , int rx) {
        if(lazy[x] == -1) return;

        if(lx != rx) { // x is not leaf node
            if(lazy[x] == 1) { // propagate the update
                lazy[RT] = lazy[LF] = 1 ;
            }else if(lazy[x] == 2) {
                lazy[RT] = lazy[LF] = 2 ;
            }else if(lazy[x] == 3) { // Invert case
                if (lazy[LF] == -1) lazy[LF] = 3;
                else if (lazy[LF] == 1) lazy[LF] = 2;
                else if (lazy[LF] == 2) lazy[LF] = 1;
                else lazy[LF] = -1;

                if (lazy[RT] == -1) lazy[RT] = 3;
                else if (lazy[RT] == 1) lazy[RT] = 2;
                else if (lazy[RT] == 2) lazy[RT] = 1;
                else lazy[RT] = -1;
            }
        }
        if(lazy[x] == 1) segment[x] = (rx - lx + 1) ;
        if(lazy[x] == 2) segment[x] = 0 ;
        if(lazy[x] == 3) segment[x] = (rx - lx + 1) - segment[x] ;
        lazy[x] = -1 ;
    }
    void updates (int l , int  r , int  x , int ty , int lx , int rx) {
        propagate(x , lx , rx) ;
        // lx rx l r lx rx
        if(l > rx or lx > r) return;
        // l lx rx r
        if(lx >= l and r >= rx) {
            lazy[x] = ty ;
            propagate(x , lx , rx) ;
            return;
        }

        updates(l , r , LF , ty , lx , md) ;
        updates(l , r , RT , ty , md + 1 , rx) ;
        segment[x] = segment[LF] + segment[RT] ;
    }
    int Query(int l , int r , int x , int lx , int rx) {
        propagate(x , lx , rx) ;
        // lx rx l r lx rx
        if(l > rx or lx > r) return 0;
        // l lx rx r
        if(lx >= l and r >= rx) {
            return segment[x];
        }
        return Query(l , r , LF , lx , md) + Query(l , r , RT , md + 1 , rx) ;
    }
};
void solve() {
    int n ; cin >> n ;
    vector<array<long long , 3>> Q(n) ;
    map<long long, long long> mp , rev_mp;
    for(int i = 0 ; i<n ; i++) {
        cin >> Q[i][0] >> Q[i][1] >> Q[i][2] ;
        mp[Q[i][1]]++ ;
        mp[Q[i][2]]++ ;
        if(Q[i][1] != 1) mp[Q[i][1] - 1]++;
        if(Q[i][2]) mp[Q[i][2] + 1]++;
    }
    mp[1LL]++;
    int idx = 1 ;
    int lst = 0 ;
    for(auto &it : mp) {
        it.second = idx ;
        rev_mp[idx] = it.first ;
        idx++;
    }
    // for(auto it : mp) cout <<it.first <<' ' <<it.second << endl;
    for(int i = 0 ; i<n ; i++) {
        Q[i][1] = mp[Q[i][1]] ;
        Q[i][2] = mp[Q[i][2]] ;
    }
    LazyPropagation lazyTree ;
    for(int i = 0 ; i < n ; i++) {
        int ty = Q[i][0] , ll = Q[i][1] , rr = Q[i][2] ;
        lazyTree.updates(ll , rr , 0 , ty , 1 , idx + 1) ;

        int ans = 1 ;
        int l = 0 , r = idx + 1 ;
        while (l <= r) {
            int mid = (l + r) / 2 ;
            if(lazyTree.Query(1 , mid , 0 , 1 , idx + 1) < mid) {
                ans = mid ;
                r = mid - 1 ;
            }else {
                l = mid + 1 ;
            }
        }
        cout << rev_mp[ans]  << endl ;
    }
}

signed main() {
    int test_cases = 1;
    //cin >> test_cases;
    while(test_cases--) {
        solve();
    }
    return 0;
}
