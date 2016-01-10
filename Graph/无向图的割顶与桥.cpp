template <typename T> bool Chkmax(T &x, T y){ return x < y? x = y, true : false; }
template <typename T> bool Chkmin(T &x, T y){ return x > y? x = y, true : false; }

const int MAXN = 20000, MAXM = 400000;
int head[MAXN], to[MAXN], next[MAXN];

bool iscut[MAXN], bccid[MAXN];
struct Tarjan{
	int low[MAXN], dfn[MAXN];
	int dfs_clock;
	
	void Dfs(int u, int fa)
	{
		low[u] = dfn[u] = ++ dfs_clock;
		
		int v, child = 0;
		for(int i = head[u];i; i = next[i]){
			v = to[i];
			if(!dfn[v]){
				child ++;
				Dfs(v, u);
				Chkmin(low[u], low[v]);
				if(low[v] < dfn[u])
					iscut[u] = true;
			}else if(dfn[v] < dfn[u] && v != fa)
				Chkmin(low[u], dfn[v]);
		}
		
		if(fa == -1 && child < 2)
			iscut[u] = false;
	}
	
	void Exec(int N){
		CLEAR(low);
		CLEAR(dfn);
		CLEAR(iscut);
		dfs_clock = 0;
		
		REP(i, 1, N)
			if(!dfn[i])
				Dfs(i, -1);
	}
};
