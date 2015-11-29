#include <cstdio>
#include <cmath>
#include <algorithm>
#define LL long long
const int MAXN = 1000000 + 1000;
int tot, cnt, pri[MAXN / 4], yz[100];
bool flag[MAXN];
void prime(int n)
{
    tot = 0;
    for (int i = 2; i <= n; i++) {
        if (!flag[i])
            pri[tot++] = i;
        for (int j = 0; i * pri[j] <= n; j++) {
            flag[i*pri[j]] = true;
            if (i % pri[j] == 0)
                break;
        }
    }
}
void ys(LL x)
{
    for(int i = 0;pri[i] <= sqrt(x); i ++){
        if(x % pri[i] == 0){
            yz[++ cnt] = pri[i];
            do x /= pri[i]; 
            while(x % pri[i] == 0);
        }
    }
    if(x != 1)
        yz[++ cnt] = x;
}

int main()
{
	int n;
	scanf("%d", &n);
	prime(n);
	ys(n);
	for(int i = 1; i <= cnt; i ++)
		if(yz[i] != yz[i - 1])
			printf("%d ", yz[i]);
	putchar('\n');
	return 0;
}
