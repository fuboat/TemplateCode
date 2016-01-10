#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}
const int MAXN = 100000 + 1000, MAXD = 32;

struct rmq{
	int maxv[MAXN][MAXD], minv[MAXN][MAXD];
	void init(int *a, int n)
	{
		REP(i, 1, n) maxv[i][0] = minv[i][0] = a[i];
		int d = log(1.0 * n)/log(2.0);
		REP(k, 1, d) REP(i, 1, n)
			if(i + (1 << k) - 1<= n){
				maxv[i][k] = max(maxv[i][k - 1], maxv[i + (1 << k - 1)][k - 1]);
				minv[i][k] = min(minv[i][k - 1], minv[i + (1 << k - 1)][k - 1]);
			}
	}
	
	void query(int l, int r, int &maxx, int &minx){
		int k = log(r - l + 1) / log(2.0);
		maxx = max(maxv[l][k], maxv[r - (1 << k) + 1][k]);
		minx = min(minv[l][k], minv[r - (1 << k) + 1][k]);
	}
}t;

int main()
{}
