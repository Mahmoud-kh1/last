#include <bits/stdc++.h>
using namespace std;
#define  int long long
const int mod = 1e9  + 7 ;
int fast(int a, int b){
    int res = 1;
    while(b){
        if(b & 1){
            res = (res * a) % mod;
        }
        b/=2;
        a = (a * a) % mod;
    }
    return res;
}
struct point{
    char ty;
    int time;
    int pos;
};
const int  N = 500;
//int dp[N][N];
//int solve(int n , int r){
//
//    int &ret = dp[n][r];
//    if(~ret)return ret;
//    ret = solve()
//}
//nc4
//!n / (4) * (n - 4)
//
//n * (n - 1) * (n - 2) * (n - 3) / (4  * 3 * 2 * )
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
//    cin >> t;
    while(t--){
        int n; cin >> n;
        int x[n], y[n];
        for(int i = 0; i < n; i++) cin >> x[i] >> y[i];

        map<array<int,4>,int>lines;
        auto ncr= [&](int n )->long long{
            if(n < 4) return 0;
            int ans = 1;
            ans = (n) * (n -1) * (n - 2) * (n - 3);
            ans /= (4 * 3 * 2);
            return ans;
        };
        map<int,int>freqx , freqy;
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                int a = y[j] - y[i];
                int b = x[j] - x[i];
                if(x[i] == x[j]){
                    freqx[x[i]]++;
                    continue;
                }
                if(y[i] == y[j]){
                    freqy[y[i]]++;
                    continue;
                }
                if (a < 0 || (a==0 && b < 0)) {
                    a = -a;
                    b = -b;
                }

                int g = gcd(abs(a), abs(b));
                a /= g;
                b/= g;
                int num = y[j] * b - a * x[j];
                int dem = b;
                g = gcd(abs(num) , abs(dem));
                num  /=g;
                dem /=g;
                lines[{a, b, num , dem}]++;
            }
        }
        int ans = 0;
        auto inLine = [&](int xx, int yy , int a, int b, int c, int d){
//            y = a / b * xx - c /d ;
//
//
//            a *xx     c
//            -----   - ----
//            b          d
//


            int dem = b * d;
            int num = a *xx * d - c * d;
            if(num % dem == 0){
                return num / dem == yy;
            }
            return false;



//             slobe = x / 0 - 0


        };
        for(auto [l, cnt] : lines){
            int L = 1 , R = 401, cur = L;
            while(L <= R){
                int mid =(L + R) / 2;
                if(mid * (mid - 1) / 2 <= cnt){
                    cur = mid;
                    L = mid + 1;
                }
                else R = mid - 1;
            }
            ans += ncr(cur);
        }
        for(auto [_, cnt] : freqx){
            int L = 1 , R = 401, cur = L;
            while(L <= R){
                int mid =(L + R) / 2;
                if(mid * (mid - 1) / 2 <= cnt){
                    cur = mid;
                    L = mid + 1;
                }
                else R = mid - 1;
            }
            ans += ncr(cur);
        }
        for(auto [_, cnt] : freqy){
            int L = 1 , R = 401, cur = L;
            while(L <= R){
                int mid =(L + R) / 2;
                if(mid * (mid - 1) / 2 <= cnt){
                    cur = mid;
                    L = mid + 1;
                }
                else R = mid - 1;
            }
            ans += ncr(cur);
        }

        cout << ans << endl;


    }

    return 0;








}
