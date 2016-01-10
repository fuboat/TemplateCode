#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define MSET(a, x) memset(a, x, sizeof(a))
#define LL long long
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}
const int MAXN = 100000 + 1000, oo = 0x7fffffff;
const LL OO = 0x7fffffffffLL;
LL sum, minx, maxx, add;
int a[MAXN], L, R, X;
struct segment{
	LL sumv[MAXN * 3], addv[MAXN * 3], maxv[MAXN * 3], minv[MAXN * 3];
	void build(int o, int l, int r)
	{
		addv[o] = 0;
		int lc = o << 1, rc = o << 1|1, M = (l + r) >> 1;
		if(l == r) addv[o] = a[l];
		else{
			build(lc, l, M);
			build(rc, M + 1, r);
		}
		maintain(o, l, r);
	}
	
	void maintain(int o, int l, int r)
	{
		int lc = o << 1, rc = o << 1|1, M = (l + r) >> 1;
		minv[o] = maxv[o] = sumv[o] = 0;
		if(l != r){
			sumv[o] = sumv[lc] + sumv[rc];
			maxv[o] = max(maxv[lc], maxv[rc]);
			minv[o] = min(maxv[lc], maxv[rc]);
		}
		sumv[o] += addv[o] * (r - l + 1);
		minv[o] += addv[o];
		maxv[o] += addv[o];
		//printf("maintain(o = %d, l = %d, r = %d, sum = %d, add = %d)\n", o, l, r, sumv[o], addv[o]);
	}
	
	void update(int o, int l, int r)
	{
		int lc = o << 1, rc = o << 1|1, M = (l + r) >> 1;
		if(L <= l && r <= R)
			addv[o] += X;
		else{
			if(L <= M) update(lc, l, M);
			if(R > M) update(rc, M + 1, r);
		}
		maintain(o, l, r);
	}
	
	void query(int o, int l, int r)
	{
		int lc = o << 1, rc = o << 1|1, M = (l + r) >> 1;
		if(L <= l && r <= R){
			sum += sumv[o] + add * (r - l + 1);
			chkmax(maxx, maxv[o] + add);
			chkmin(minx, minv[o] + add);
		}
		else{
			add += addv[o];
			if(L <= M) query(lc, l, M);
			if(R > M) query(rc, M + 1, r);
			add -= addv[o];
		}
	}
}t;

int main()
{
	int n, m;
	char c[10];
	while(scanf("%d%d", &n, &m) == 2)
	{
		REP(i, 1, n) scanf("%d", &a[i]);
		t.build(1, 1, n);
		REP(i, 1, m){
			scanf("%s", c);
			if(c[0] == 'Q'){
				scanf("%d%d", &L, &R);
				sum = 0; maxx = OO, minx = -OO;
				t.query(1, 1, n);
				printf("%lld %lld %lld\n", sum, maxx, minx);
			}
			else{
				scanf("%d%d%d", &L, &R, &X);
				t.update(1, 1, n);
			}
		}
	}
}
