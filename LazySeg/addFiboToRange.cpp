#include <bits/stdc++.h>
#define task "testing"
#define int long long
#define multitest 0
using namespace std;

const int N = 3e5+10, mod = 1e9+9;

int n, a[N+5], fib[N+5], bit[N+5][3];

int f(int k) {
	return (k >= 0 ? fib[k] : (k&1 ? fib[-k] : mod-fib[-k]));
}

void upd(int p, vector<int> v) {
    for (; p <= n; p += (p&-p)) {
		for (int x = 0; x < 3; x++) {
			(bit[p][x] += v[x]) %= mod;
		}
	}
}

int qry(int p) {
	int sm[] = {0, 0, 0}, k = p;
	
	for (; p > 0; p -= (p&-p)) {
		for (int x = 0; x < 3; x++) {
			(sm[x] += bit[p][x]) %= mod;
		}
	}
	
	return ((sm[0]*f(k))%mod+(sm[1]*f(k+1))%mod+sm[2])%mod;
}

void flo(int ID) {
	int m; cin >> n >> m;
	
	for (int x = 1; x <= n; x++) {
		cin >> a[x];
		
		(a[x] += a[x-1]) %= mod;
	}
	
	while (m--) {
		int type, l, r; cin >> type >> l >> r;
		
		if (type == 1) {
			upd(l, {f(2-l), f(3-l), mod-1});
			
			upd(r+1, {mod-f(2-l), mod-f(3-l), f(r-l+3)});
		}
		else {
			int smf = (qry(r)-qry(l-1)+mod)%mod;
			
			int sma = (a[r]-a[l-1]+mod)%mod;
			
			cout << (sma+smf)%mod << "\n";
		}
	}
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    if (fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
		freopen(task".out", "w", stdout);
    }
    
    fib[1] = fib[2] = 1;
    
    for (int x = 3; x <= N; x++) {
    	fib[x] = (fib[x-1]+fib[x-2])%mod;
	}
	    
    int TCS = 1, ID = 1;
    
    if (multitest) {
        cin >> TCS;
    }
    
    while (TCS--) flo(ID++);
    
    return 0;
}
