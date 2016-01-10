/*
	注意：
	1. 不管插入几个字符串， 请在每个串尾加一个标识符， 否则在排序时可能出错； 
	2. 本代码不鲁棒， 请按题意适当修改代码；
*/ 
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define CLEAR(a) memset(a, 0, sizeof(a))
const int MAXN = 100000 + 1000, MAXM = MAXN, MAXD = 23;
int c[MAXN];
inline void jsort(int *s, int *rank, int *sa, int m, int n)//双关键字基数排序 
{
	//s[i]表示编号为i二元组的第一关键字;
	//rank[i]表示按第二关键字排名且名次为i的二元组编号，sa[i]表示按二元组排名且名次为i的二元组编号; 
	CLEAR(c);
	REP(i, 0, n - 1) c[s[rank[i]]] ++;//入桶;
	REP(i, 1, m - 1) c[i] += c[i - 1];//用桶统计名次; 
	rep(i, n - 1, 0) sa[-- c[s[rank[i]]]] = rank[i];//借用桶，用sa存储名次;
}
int n;
struct rmq{
	int minv[MAXN][MAXD];
	void Init(int *a, int n)
	{
		REP(i, 0, n - 1) minv[i][0] = a[i];
		int d = log(1.0 * n) / log(2.0);
		REP(k, 1, d) REP(i, 0, n - 1)
			if(i + (1 << k) - 1 <= n)
				minv[i][k] = min(minv[i][k - 1], minv[i + (1 << (k - 1))][k - 1]);
	}
	
	int Query(int l, int r){
		int k = log(r - l + 1) / log(2.0);
		return min(minv[l][k], minv[r - (1 << k) + 1][k]);
	}
};
struct suffix_array{
	int tmp[MAXN], t2[MAXN], t1[MAXN], s[MAXN], sa[MAXN], height[MAXN];
	rmq t;
	char T[MAXN];
	void Init()
	{
	CLEAR(s); CLEAR(sa); CLEAR(rank); CLEAR(t1); CLEAR(t2); CLEAR(tmp); CLEAR(height);
	}
	void buildSA(int m)
	{
		int *x = t1, *y = t2;
		REP(i, 0, n - 1)
			tmp[i] = i, x[i] = s[i]; 
		jsort(x, tmp, sa, m, n);
		for(int k = 1; k <= n; k <<= 1){
			int p = 0, now, last;
			REP(i, n - k, n - 1) y[p ++] = i;
			REP(i, 0, n - 1) if(sa[i] >= k) y[p ++] = sa[i] - k;
			jsort(x, y, sa, m, n);
			swap(x, y);
			p = 1;
			x[sa[0]] = 0;
			REP(i, 1, n - 1){
				now = sa[i], last = sa[i - 1];
				x[now] = y[now] == y[last] && y[now + k] == y[last + k]? p - 1 : p ++;
			}
			if(p >= n) break;
			m = p;
		}
	}
	int lenp;
	int CMP_suffix(char *pattern, int p){ return strncmp(pattern, T + sa[p], lenp); }
	int Find(char *P)
	{
		lenp = strlen(P);
		if(CMP_suffix(P, 0) < 0) return -1;
		if(CMP_suffix(P, n - 1) > 0) return -1;
		int l = 0, r = n - 1;
		while(l <= r){
			int mid = (l + r) >> 1;
			int res = CMP_suffix(P, mid);
			if(!mid) return mid;
			else if(mid < 0) r = mid - 1;
			else l = mid + 1;
		}
		return -1;
	}
	int rank[MAXN];
	void getHeight()
	{
		int k = 0;
		REP(i, 0, n - 1) rank[sa[i]] = i;
		REP(i, 0, n - 1){
			if(k) k --;
			if(rank[i] == 0){ k = 0; continue; }
			int j = sa[rank[i] - 1];
			while(s[i + k] == s[j + k])
				k ++;
			height[rank[i]] = k;
		}
	}
	int Query(int l, int r)
	{
		if(l == r) return n - l;
		int x = rank[l], y = rank[r];
		if(x > y) swap(x, y);
		return t.Query(x + 1, y);
	}
};
int main()
{
	
}
