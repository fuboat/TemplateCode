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
const int MAXC = 100000 + 10000, oo = 0x7fffffff;
int D, L, R, sum, maxx, minx, add;
int flag;
struct segment{
	int addv[MAXC * 3], setv[MAXC * 3], maxv[MAXC * 3], minv[MAXC * 3], sumv[MAXC * 3];
	void pushdown(int o)
	{
		int lc = o << 1, rc = o << 1|1;
		if(setv[o] != -1){
			setv[lc] = setv[rc] = setv[o];
			addv[lc] = addv[rc] = 0;
			setv[o] = -1;
		}else{
			if(setv[lc] != -1) setv[lc] += addv[o];
			else addv[lc] += addv[o];
			if(setv[rc] != -1) setv[rc] += addv[o];
			else addv[rc] += addv[o];
			addv[o] = 0;
		}
	}
	
	void maintain(int o, int l, int r)
	{
		int lc = o << 1, rc = o << 1|1;
		if(setv[o] != -1){
			sumv[o] = setv[o] * (r - l + 1);
			maxv[o] = minv[o] = setv[o];
		}else if(l != r){
			sumv[o] = sumv[lc] + sumv[rc] + addv[o] * (r - l + 1);
			maxv[o] = max(maxv[lc], maxv[rc]) + addv[o];
			minv[o] = min(minv[lc], minv[rc]) + addv[o];
		}else sumv[o] = maxv[o] = minv[o] = addv[o];
	}
	
	void update(int o, int l, int r)
	{
		if(L <= l && r <= R){
			if(flag == 1){		//add
				if(setv[o] != -1) setv[o] += D;
				else addv[o] += D;
			}else addv[o] = 0, setv[o] = D; //set
		}else{
			pushdown(o);
			int mid = (l + r) >> 1;
			if(L <= mid) update(o << 1, l, mid);
			else maintain(o << 1, l, mid);
			if(mid < R) update(o << 1|1, mid + 1, r);
			else maintain(o << 1|1, mid + 1, r);
		}
		maintain(o, l, r);
	}
	
	void query(int o, int l, int r)
	{
		if(setv[o] != -1){
			int v = setv[o];
			sum += v * (min(R, r) - max(L, l) + 1);
			chkmax(maxx, v + add);
			chkmin(minx, v + add);
		}
		else if(L <= l && r <= R){
			sum += sumv[o];
			chkmax(maxx, maxv[o] + add);
			chkmin(minx, minv[o] + add);
		}
		else{
			int mid = (l + r) >> 1;
			sum += addv[o] * (min(R, r) - max(L, l) + 1);
			add += addv[o];
			if(L <= mid) query(o << 1, l, mid);
			if(mid < R) query(o << 1|1, mid + 1, r);
			add -= addv[o];
		}
	}
};

int main(){}
