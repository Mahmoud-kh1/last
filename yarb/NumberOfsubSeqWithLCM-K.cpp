#include <bits/stdc++.h>
using namespace std;
#define int long long

void Yasser() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(0);
}
vector<int> factors(int n) {
    vector<int> ret ;
    for(int i = 2 ; i*i <= n ; i++) {
        int value = 1 ;
        while (n % i == 0) {
            n/=i ;
            value*=i;
        }
        if(value > 1) ret.push_back(value) ;
    }
    if(n > 1) ret.push_back(n) ;

    return ret ;
}
const int Mod = 998244353 ;
const int N = 2e5 + 5 , M = (1 << 13) ;
int mask[M] , dp[M][M] , Cost[N] , P_2[N];
vector<int> LCM ;
int calc(int i , int maskk) {
    if(i == M) {
        return (maskk == (1 << LCM.size()) - 1) ;
    }
    int &ret = dp[i][maskk] ;
    if(~ret) return ret ;

    ret = calc(i + 1 , maskk) ;

    ret= calc(i+1,maskk);
    ret=ret + (calc(i+1,maskk|i)*(P_2[mask[i]]-1+Mod)%Mod)%Mod;
    if (ret>=Mod)ret-=Mod;
    return ret;
}
signed main() {
    Yasser();
    int tt = 1;
    //cin >> tt;
    while (tt--) {
        int n , m ; cin>>n>>m;

        P_2[0] = 1 ;
        for(int i = 1 ; i<=n ; i++) {
            P_2[i] = P_2[i - 1] * 2 % Mod ;
        }
        LCM = factors(m) ;
        for(int i = 0 ; i<n ; i++) {
            int x ; cin>>x ;
            int ms = 0 ;
            if(m % x) continue;
            for(int j = 0 ; j<LCM.size() ; j++) {
                if(x % LCM[j] == 0 ) {
                    ms |= (1 << j) ;
                }
            }
            mask[ms]++;
        }
        if (m==1){
            cout<<(P_2[mask[0]]-1+Mod)%Mod;
            return 0 ;
        }
        memset(dp , -1 , sizeof(dp)) ;
        int ans = calc(0 , 0) ;

        cout<<ans ;
    }

}
