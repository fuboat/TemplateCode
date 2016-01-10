#include <cstdio>
#include <algorithm>
#include <iostream>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define lc son[o][0]
#define rc son[o][1]
const int MAXN = 80000 + 1000;
struct Splay_tree{
	int son[MAXN][2];
	int sumv[MAXN], num[MAXN], fa[MAXN], fnum[MAXN];
	int root;
	void Maintain(int o){ sumv[o] = sumv[lc] + sumv[rc] + 1; }
	void Pushdown(int o){}
	void Rotate(int o)
	{
		int pa = fa[o], up = fa[pa];
		bool d = (o == son[pa][1]);
		// Make sure whether or not it is left-turn;
		// if d == 1, it is left-turn;
		// else, it is right turn;
		Pushdown(pa); // We should Pushdown 'pa' first because 'pa' is the father of 'o';
		Pushdown(o);  // 'Pushdown' may change the sons of node 'o';
		int c = son[o][!d]; // So, this step must be later than the last one;
		son[fa[o] = up][pa == son[up][1]] = o;
		// Exchange the fathers of 'pa' and 'o';
		// 'pa == son[up][1]' is for making sure the direct of turning;
		son[fa[c] = pa][d] = c; // Build the relationship between 'c' and 'pa';
		son[fa[pa] = o][!d] = pa; // Update the relationship between 'pa' and 'o';
		Maintain(pa); // Do this first, because now 'o' is the father of 'pa';
		Maintain(o);
	}
	void Splay(int o, int F){
		if(!o) return ;
		while(fa[o] != F){
			int pa = fa[o], up = fa[pa];
			if(up == F){ Rotate(o); break; }
			else if((son[up][0] == pa) ^ (son[pa][0] == o))
			// If the value is true, the three node('o', 'pa', 'up') is on the same line(三点共线); 
				Rotate(pa), Rotate(o);
			else Rotate(o), Rotate(o);
		}
		if(!F) root = o;
	}
	int Get(int o, bool d)
	{
		if(!o) return 0;
		while(son[o][d]) o = son[o][d];
		return o;
		// Find the biggest(or smallest) one under the node 'o';
	}
};
