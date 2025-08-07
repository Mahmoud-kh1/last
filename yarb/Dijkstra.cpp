#include <bits/stdc++.h>
using namespace std;
void fast() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}
int main(){
    int n , m ,k ; cin >> n >> m >> k;
    vector<vector<int>> adj(n + 1) ;
    for(int i = 0 ; i < m ; i++) {
        int u , v; cin >>u >> v ;
        adj[u].push_back(v) ;
        adj[v].push_back(u) ;
    }
    map<tuple<int , int , int> , int> bad ;
    for(int i = 0 ; i < k ; i++) {
        int u , v , x ; cin >> u >> v >> x ;
        bad[{u , v , x}]++ ;
    }

    priority_queue<array<int , 3> , vector<array<int , 3>> , greater<>> pq ;
    pq.push({0 , 0 , 1}) ;
    vector<vector<int>> d(n + 1 , vector<int> (n + 1 , INT_MAX)) ;
    d[0][1] = 0 ;
    vector<vector<int>> par(n + 1 , vector<int> (n + 1 , -1)) ;
    par[0][1] = -1 ;
    while (pq.size()) {
        auto[c , v , cur] = pq.top() ;
        pq.pop() ;
        if(d[v][cur] != c) continue;

        for(auto it : adj[cur]) {
            tuple<int , int , int> cy = {v , cur , it} ;
            if(bad.find(cy) != bad.end()) continue;
            else if(d[cur][it] > c + 1) {
                par[it][cur] = v ;
                d[cur][it] = c + 1 ;
                pq.push({c + 1 , cur , it}) ;
            }
        }
    }
    if(*min_element(d[n].begin() , d[n].end()) == INT_MAX) {
        cout << -1 << '\n' ;
        return 0 ;
    }
    int best = INT_MAX, best_prev = -1;
    for (int prev = 1; prev <= n; ++prev) {
        if (d[prev][n] < best) {
            best = d[prev][n];
            best_prev = prev;
        }
    }
    if (best == INT_MAX) {
        cout << -1 << "\n";
        return 0;
    }
    cout << best << '\n' ;
    int cur1 = n , cur2 = best_prev;
    vector<int> path ;
    path.push_back(n) ;
    path.push_back(cur2) ;
    while (par[cur1][cur2] != 0) {
        int x = par[cur1][cur2] ;
        cur1 = cur2 ;
        cur2 = x ;
        path.push_back(x) ;
    }
    reverse(path.begin(), path.end()) ;
    for(auto it : path) cout << it <<' ' ;
    return 0;
}
