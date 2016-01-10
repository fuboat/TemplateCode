const int MAXN = 100000, MAXM = 1000000;
bool mark[MAXN];
/*Edge-------------------------------*/
int head[MAXN];
int to[MAXM], next[MAXM];
/*TwoSAT-----------------------------*/
struct TwoSAT{
	int st[MAXN];
	int top;
	// Stack;
	bool Dfs(int u)
	{
		if(mark[u ^ 1])
			return false;
		if(mark[u])
			return true;
		
		st[++ top] = u;
		mark[u] = true;
		for(int i = head[u]; i; i = next[i])
			if(!Dfs(to[i]))
				return false;
		return true;
	}
	bool Exec(int n)
	{
		for(int i = 0; i < n * 2; i += 2){
			if(mark[i] || mark[i ^ 1])
				continue;

			top = 0;
			if(!Dfs(i)){
				while(top)
					mark[st[top --]] = false;
				if(!Dfs(i ^ 1))
					return false;
			}
		}
		return true;
	}
};
