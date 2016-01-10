#ifdef WIN32
	#define ll "%I64d"
#else
	#define ll "%lld"
#endif
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long

template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}

void getFail(char* P, int* f)
{
	int m = strlen(P);
	f[0] = 0; f[1] = 0;
	REP(i, 1, m){
		int j = f[i];
		while(j && P[i] != P[j]) j = f[j];
		f[i + 1] = P[i] == P[j]? j + 1 : 0;
	}
}

void find(char* T, char* P, int *f)
{
	int n = strlen(T), m = strlen(P);
	getFail(P, f);
	int j = 0;
	REP(i, 0, n - 1){
		while(j && P[j] != T[i]) j = f[j];
		if(P[j] == T[i]) j ++;
		if(j == m) printf("%d\n", i - m + 1);
	}
}
int main()
{}
