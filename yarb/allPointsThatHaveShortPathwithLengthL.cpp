#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long

void fast() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(0);
}
#define endl "\n"
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).begin(), (x).end(), greater<int>()
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
char direction[4] = {'D', 'R', 'U', 'L'};

signed main() {
    fast() ;
    int n , m , source ; cin>>n>>m>>source ;
    vector<vector<pair<int , int>>> adj(n + 1) ;
    vector<pair<pair<int , int> , int>> Edges;

    for(int i = 0 , u , v , c ; i < m ; i++) {
        cin>>u>>v>>c ;
        adj[u].emplace_back(v , c) ;
        adj[v].emplace_back(u , c) ;
        Edges.push_back({{u,v} , c});
    }
    int l ; cin>>l ;
    priority_queue<pair<int , int> , vector<pair<int , int>> , greater<pair<int , int>>> pq ;
    pq.emplace(0 , source) ;
    vector<int> Distance(n+1 , LLONG_MAX) ; // Minimum distance from the source to the destination .
    Distance[source] = 0 ;
    while (!pq.empty()) {
        auto[cost , node] = pq.top() ;
        pq.pop() ;
        if(cost != Distance[node]) continue;
        for (auto [nxt , w] : adj[node]) {
            if(Distance[nxt] > w + cost) {
                Distance[nxt] = w + cost ;
                pq.emplace(w + cost , nxt) ;
            }
        }
    }
    int cnt = 0 ;
    //for(int i = 1 ; i<=n ; i++) cout<<Distance[i] <<' ' ;
    for(int i = 1 ; i<=n ; i++) cnt += (Distance[i] == l) ;

    for(auto &it : Edges){
        int u = it.first.first , v = it.first.second , w = it.second;
        int rem = l - Distance[u];
        // if the distance to the other node is greater .
        if(rem > 0 && rem < w){
            int disf2 = Distance[v] + (w - rem);
            if(disf2 >= l) cnt++;
        }
        rem = l - Distance[v];
        if(rem > 0 && rem < w){
            int disf2 = Distance[u] + (w - rem);
            if(disf2 > l) cnt++;
        }
    }
    cout<<cnt ;
    return 0;
}
