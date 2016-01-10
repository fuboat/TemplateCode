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

const int MAXNODE = 1000000, MAXS = 30;

struct Trie{
	int ch[MAXNODE][MAXS];
	int val[MAXNODE];
	int sz;
	Trie(){sz = 1; memset(ch[0], 0, sizeof(0));}
	inline int idx(char c){ return c - 'a'; }
	void insert(char *s, int v)
	{
		int u = 0, len = strlen(s);
		REP(i, 0, len - 1){
			int c = idx(s[i]);
			if(!ch[u][c]){
				memset(ch[sz], 0, sizeof(sz));
				ch[u][c] = ++ sz;
				val[sz] = 0;
			}
			u = ch[u][c];
		}
		val[u] = v;
	}
};

int main()
{}
