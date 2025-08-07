// for gcd i if the subseq a1, a2 have gcd i , and a3 a4 also , dp[i] is (a1 *  a2) + (a3 * a4) , sum of mul of sequences that have gcd i

#include <bits/stdc++.h>
using namespace std;
#define  int long long
const int N = 1e6  + 7, mod = 1e9 + 7;
int phi[N + 4], freq[N + 1];
int dp[N + 8]{};
void computePhi(){
    for(int i = 1; i <= N; i++){
        phi[i] = i, freq[i] = 1;
        }

        for(int p = 2; p <= N; p++){
             if(phi[p] == p){
                 phi[p] = p - 1;
                 for(int i = 2 * p ; i <= N; i+= p){
                     phi[i] = (phi[i] / p) * (p  - 1);
                 }
             }
        }
}
int fast(int a, int b){
    int res = 1;
    while(b){
        if(b & 1){
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        b /= 2;
    }
    return res;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
//    cin >> t;
    computePhi();
    while(t--){
        int n; cin >> n;
        int a[n];
        for(int i = 0; i < n; i++){
            cin >> a[i];
            int cur = a[i];
            cur = (cur *  fast(phi[a[i]], mod - 2)) % mod; // this line if for the problem iteslf 
            cur++;
            if(cur >= mod) cur-=mod;
            freq[a[i]] =freq[a[i]] *  cur % mod;
            if(freq[a[i]] >= mod) freq[a[i]] -=mod;
        }

        for(int i = N; i >= 1; i--){
            int mul = 1;
            for(int j = i; j <= N; j+= i){
                mul =mul * freq[j] % mod;
                if(j != i) dp[i]-= dp[j];
                if(dp[i] < 0) dp[i] += mod;
            }
            mul--;
            if(mul <0 ) mul+= mod;
            dp[i]+= mul;
            if(dp[i] >= mod) dp[i] -=mod;
        }
        int ans=  0;
        for(int i = 1; i <= N; i++){
            ans += (dp[i] * fast(i, mod - 2)) % mod;
            if(ans >= mod) ans -=mod;
        }
        cout << ans << endl;

    }

    return 0;












}
