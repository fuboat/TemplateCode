#include <cstdio>
#include <cmath>
bool is_prime(int n)
{
    int end = sqrt(n);
    for(int i = 2; i <= end; i ++)
        if(n % i == 0) return 0;
    return 1;
}
int main(){}
