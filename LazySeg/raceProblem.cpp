// You are a car race organizer and would like to arrange some races in Linear Kingdom.

// Linear Kingdom has n consecutive roads spanning from left to right. The roads are numbered from 1 to n from left to right, thus the roads follow in the order of their numbers' increasing. There will be several races that may be held on these roads. Each race will use a consecutive subset of these roads. Also, each race will pay some amount of money to you if this race is held. No races overlap in time, so some roads can be used in several races.

// Unfortunately, some of the roads are in a bad condition and they need repair. Each road has repair costs associated with it, you are required to pay this cost to repair the road. A race can only take place if all the roads used in the race are renovated. Your task is to repair such roads (possibly all or none) that will maximize your profit. Your profit is defined as the total money you get from the races that are held minus the total money you spent to repair the roads. Note that you may decide not to repair any road and gain zero profit.

// Print the maximum profit you can gain.

// Input
// The first line contains two single-space separated integers, n and m (1 ≤ n, m ≤ 2·105), denoting the number of roads and the number of races, respectively.

// Then n lines follow, each line will contain a single non-negative integer not exceeding 109 denoting the cost to repair a road. The costs are given in order from road 1 to road n.

// Finally, m lines follow. Each line is single-space-separated triplets of integers. Each triplet will be given as lb, ub, and p (1 ≤ lb ≤ ub ≤ n, 1 ≤ p ≤ 109), which means that the race these three integers describe will use all the roads from lb to ub, inclusive, and if it's held you get p.

// Output
// Print a single integer denoting the maximum possible profit you can gain.

// Please, do not use the %lld specificator to read or write 64-bit integers in C++. It is recommended to use cin, cout stream (also you may use %I64d specificator).

#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll N=2e5+5;
ll n,m,q,a[N],tag[N<<2],t[N<<2],f[N],l,r,x,ans;
void pushup(ll u){
	t[u]=max(t[u*2],t[u*2+1]);
}
void mvtag(ll u,ll x){
	t[u]+=x;tag[u]+=x;
}
void pushdown(ll u,ll l,ll r){
	if(!tag[u])return;
	mvtag(u*2,tag[u]);mvtag(u*2+1,tag[u]);
	tag[u]=0;
}
void upd(ll u,ll l,ll r,ll ql,ll qr,ll x){
	if(qr<l||r<ql)return;
	if(ql<=l&&r<=qr){mvtag(u,x);return;}
	pushdown(u,l,r);
	ll mid=l+r>>1;
	upd(u*2,l,mid,ql,qr,x);upd(u*2+1,mid+1,r,ql,qr,x);
	pushup(u);
}
ll query(ll u,ll l,ll r,ll ql,ll qr){
	if(qr<l||r<ql)return 0;
	if(ql<=l&&r<=qr)return t[u];
	pushdown(u,l,r);
	ll mid=l+r>>1;
	return max(query(u*2,l,mid,ql,qr),query(u*2+1,mid+1,r,ql,qr));
}
struct inv{ll l,x;};
vector<inv>b[N];
int main(){
	cin>>n>>m;
	for(ll i=1;i<=n;i++)cin>>a[i];
	for(ll i=1;i<=m;i++){
		cin>>l>>r>>x;
		b[r].push_back({l,x});
	}
	for(ll i=1;i<=n;i++){
		upd(1,1,n,i,i,ans);upd(1,1,n,1,i,-a[i]);
		for(auto e:b[i]){
			upd(1,1,n,1,e.l,e.x);
		}
		ans=max(query(1,1,n,1,i),ans);
	}
	cout<<ans<<'\n';
	return 0;
}
