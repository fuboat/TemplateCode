const int MAXN = 1000000 + 1000;
int tot, pri[MAXN / 4];
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
int main(){}
