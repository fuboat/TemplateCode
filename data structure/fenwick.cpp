#include <cstdio>
const int MAXN = 15000 + 100, MAXX = 320000 + 1000;

#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
struct fenwick{
	int s[MAXN];
	void add(int pos, int x)
	{
		while(pos <= n){
			s[pos] += x;
			pos += pos & -pos;
		}
	}
	
	int sum(int pos)
	{
		int sum = 0;
		while(pos > 0){
			sum += s[pos];
			pos -= pos & -pos;
		}
		return sum;
	}
}t;
