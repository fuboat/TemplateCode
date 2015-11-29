#include <cstdio>
#include <cstdlib>
#ifdef WIN32
	#define ll "%I64d"
#else
	#define ll "%lld"
#endif
#define LL long long
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)

int test[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

LL ksc(LL x, LL y, LL mod)
{
	if(!y) return 0;
	if(y == 1) return x;
	LL tmp = ksc(x, y / 2, mod);
	if(y & 1) return ((tmp << 1) % mod + x) % mod;
		return (tmp << 1) % mod;
}

LL ksm(LL b, LL p, LL mod)
{
	
	if(p == 1) return b % mod;
	if(p == 0) return 1;
	LL tmp = ksm(b, p/2, mod);
	if(1 & p) return ksc(ksc(tmp, tmp, mod), b, mod);
	return ksc(tmp, tmp, mod);
}

bool check(LL x, LL md)
{
	LL S = 1, y = md - 1, tx;
	while(y)
	{
		if(y & 1) S = ksc(S, x, md);
		tx = x;
		x = ksc(x, x, md);
		if(x == 1 && tx != 1 && tx != md - 1) return 0;
		y >>= 1;
	}
	if (S == 1) return 1;
	else return 0;
}

bool mr(LL x)
{
	if(x == 2) return 1;
	if(!(x % 2)) return 0;
	REP(i, 0, 9)
	if(x <= test[i]) break;
	else if(check(test[i], x) != 1)
			return 0;	
	return 1;
}

int main()
{
	LL x;
	scanf(ll, &x);
	if(mr(x)) printf("Yes\n");
	else printf("No\n");
	return 0;
}
