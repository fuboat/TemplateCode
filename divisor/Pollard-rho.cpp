//many parts of the code are from the Internet, so you can find the information about them on Internet if you want
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <ctime>
#define LL long long
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i++)
int test[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
LL yz[70];		//the number with most prime divistor is 2 ^ 64(the limitation of long long), so 70 is enough
int cnt;
LL ksc(LL x, LL y, LL mod)		//return (x * y) % mod
{
    if(!y) return 0;
    if(y == 1) return x;
    LL tmp = ksc(x, y / 2, mod);
    if(y & 1) return ((tmp << 1) % mod + x) % mod;
        return (tmp << 1) % mod;
}

LL ksm(LL b, LL p, LL mod)		//return (b ^ p) % mod
{
    if(p == 1) return b % mod;
    if(p == 0) return 1;
    LL tmp = ksm(b, p/2, mod);
    if(1 & p) return ksc(ksc(tmp, tmp, mod), b, mod);
    return ksc(tmp, tmp, mod);
}

LL gcd(LL a, LL b)
{
	LL r = a % b;
	while(r){
		a = b; b = r; r = a % b;
	}
	return b;
}

bool check(LL x, LL md)
{
	LL S = 1, y = md - 1, tx;
	while(y)
	{
		if(y & 1) S = ksc(S, x, md) % md;
		tx = x;
		x = ksc(x, x, md) % md;
		if(x == 1 && tx != 1 && tx != md - 1) return 0;
		y >>= 1;
	}
	if (S == 1) return 1;
	else return 0;
}

bool mr(LL x)		//Miller-Rabbin
{
	if(x == 2) return 1;
	if(!(x % 2)) return 0;
	REP(i, 0, 9) if(x == test[i]) return true;
	REP(i, 0, 9)
	if(x <= test[i]) break;
	else if(check(test[i], x) != 1)
			return 0;
	return 1;
}

void rho(LL n)		//pollard-rho
{
    if(n == 4){
        rho(2);
        return;
    }
    if(mr(n)){		//check if it is a prime
        yz[++ cnt] = n;
        return;
    }
    LL x, y, d;
    int i = 1, k = 2;
    y = x = rand() % (n - 1) + 1;
    while (true) {
        ++i;
        x = (ksc(x, x, n) + 1) % n;
        if(x == y){
            y = x = rand() % (n - 1) + 1;
            i = 1; k = 2;
        }
        if(y > x) d = gcd(y - x, n);
        else d = gcd(x - y, n);
        if (1 < d && d < n){
            rho(d);
            while(n % d == 0)
                n /= d;
            rho(n);
            return ;
        }
        if (i == k)
            y = x, k <<= 1;
    }
}
#ifdef WIN32
#define ll "%I64d"
#else
#define ll "%lld"
#endif
int main()
{
	srand(time(0));
	LL x;
	scanf(ll, x);
	rho(n);
	std::sort(yz + 1, yz + cnt + 1);
	for(int i = 1; i <= cnt; i ++)
		if(yz[i] != 1 && yz[i] != yz[i - 1])
			printf(ll" ", yz[i]);
	puts("");
}
	
