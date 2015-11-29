#define REP(i, x, y)  for(int i = x, _ = y; i <= _; i ++)
#include <cstdio>

const int MAXA = 1000000;
bool flag[MAXA + 1];
int zyz[MAXA + 1];

void prime(int n)
{
	REP(i, 2, n){
		if(!flag[i]){
			zyz[i] = 0;
			REP(j, 2, n){
				if(j * i > n)
					break;
				zyz[j * i] ++;
				flag[j * i] = 1;
			}
		}
	}
}

int main()
{
	int n;
	scanf("%d", &n);
	prime(n);
	printf("%d\n", zyz[n]);
}
