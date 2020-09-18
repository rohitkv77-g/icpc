/*
	Author: Rohit Verma
	Problem Link: https://codeforces.com/contest/628/problem/D
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define ALL(a) a.begin(), a.end()
#define RALL(a) a.rbegin(), a.rend()
#define pb push_back
#define MOD 1000000007
#define sz5 100005
#define sz6 1000005
#define UP upper_bound
#define LB lower_bound
#define F first
#define S second
#define PI pair<int,int>
#define PL pair<ll,ll>
#define VI vector<int>
#define VL vector<ll>

string a, b;
ll m, d, R[2002];
ll dp[2002][2002][2];
bool mk[2002][2002][2];

ll is(string &a){
	ll rem=0;
	for(int la=0;la<a.length();la++){
		rem=(rem+((a[la]-'0')*R[a.length()-la])%m)%m;
		if(la%2==0 && a[la]==d+'0')
			return 0;
		if(la%2==1 && a[la]!=d+'0')
			return 0;
	}
	if(rem==0)
		return 1;
	return 0;
}

ll solve(string &st, ll pos, ll rem, bool f){
	if(pos==st.length()+1){
		if(rem==0)
			return 1;
		return 0;
	}
	if(mk[pos][rem][f])
		return dp[pos][rem][f];
	mk[pos][rem][f]=true;
	ll LMT;
	if(f==0){
		LMT=9;
	}else{
		LMT=st[pos-1]-'0';
	}

	ll p=st.length()-pos+1;
	for(int la=0;la<=LMT;la++){
		if(pos%2==1 && la==d)
			continue;
		if(pos%2==0 && la!=d)
			continue;
		ll currem=((R[p]*la)%MOD+rem)%m;
		bool curf=0;
		if(f==1 && la==LMT)
			curf=1;
		dp[pos][rem][f]=(dp[pos][rem][f] + solve(st, pos+1, currem, curf))%MOD;
	}

	return dp[pos][rem][f];
	
}

int main() {
	FAST

	#ifndef ONLINE_JUDGE
		freopen("in", "r", stdin);
		// freopen("out", "w", stdout);
	#endif

	ll la,lb;
	cin>>m>>d>>a>>b;

	R[1]=1;
	for(la=2;la<=2000;la++){
		R[la]=(R[la-1]*10)%m;
	}

	ll ans=solve(b, 1, 0, 1);
	memset(dp, 0, sizeof(dp));
	memset(mk, 0, sizeof(mk));
	ans-=solve(a, 1, 0, 1);
	ans+=(is(a)+MOD)%MOD;
	while(ans<0)	
		ans+=MOD;

	cout<<ans<<endl;
	return 0;
}
